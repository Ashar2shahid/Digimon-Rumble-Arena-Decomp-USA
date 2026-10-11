"""Prepare and optionally run a bounded, private native decomp-permuter batch.

Example:
  python tools/permuter_batch.py game:func_800AEFC4=analysis/us/game/main_sol_48F48_func_800AEFC4_near.c
  python tools/permuter_batch.py --run --timeout 60 --jobs 2 game:func_800AEFC4=...

Preparation is a gate: compile the seed in its actual source slot and alone,
compare both with retail bytes and all recovered siblings, then score the
function-only object. Search outputs are diagnostic and are never landed.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time

import build_dra as B
from check_unit import object_symbols
from probe_slot import compare_words, original_size
from source_inventory import ROOT, UNITS, manifest, mask, sdk_symbols, source_functions

OUT = ROOT / "analysis/us/workflow/permuter_batch"
PERMUTER = ROOT / ".tools/decomp-permuter"


def command(args, *, env=None):
    proc = subprocess.run([str(x) for x in args], cwd=ROOT, env=env,
                          capture_output=True, text=True)
    if proc.returncode:
        raise RuntimeError(f"command failed ({proc.returncode}): {args}\n{proc.stdout}\n{proc.stderr}")
    return proc.stdout


def canonical_toolchain(unit, slot):
    key = f"{unit}/{slot}"
    cc1, flags, maspsx, asflags = B.unit_toolchain(unit, slot)
    if key in B.UNIT_MASPSX_VER:
        maspsx = [x for x in maspsx if not x.startswith("--aspsx-version=")]
        maspsx.append("--aspsx-version=" + str(B.UNIT_MASPSX_VER[key]))
    return cc1, flags, maspsx, asflags


def compile_source(source, output, unit, slot):
    """Mirror build_dra's per-file native preprocessing, cc1 and maspsx path."""
    key = f"{unit}/{slot}"
    cc1, flags, maspsx, asflags = canonical_toolchain(unit, slot)
    output.parent.mkdir(parents=True, exist_ok=True)
    intermediate = output.with_suffix(".i")
    assembly = output.with_suffix(".s")
    env = dict(os.environ)
    tmp = output.parent / "tmp"
    tmp.mkdir(exist_ok=True)
    env["TMPDIR"] = str(tmp)
    in_func = (["-DINCLUDE_ASM_IN_FUNC"] if any(re.fullmatch(r"-G[1-9]\d*", f) for f in flags)
               or "-O3" in flags else [])
    if B.UNIT_CXX.get(key):
        cpp = B.cxx_cpp_bin()
        if Path(cpp).name.upper() == "CPPPSX.EXE":
            cpp_cmd = [cpp, "-I", "include", "-I", B.BUILD, "-DVER_USA", "-D__cplusplus",
                       *in_func, source, intermediate]
        else:
            cpp_cmd = [cpp, *[f for f in B.CPP_FLAGS if f != "-D_LANGUAGE_C"],
                       *in_func, "-D__cplusplus", "-o", intermediate, source]
    else:
        cpp_cmd = [B.cpp_bin(), *B.CPP_FLAGS, *in_func, "-o", intermediate, source]
    command(cpp_cmd, env=env)
    command([cc1, *flags, "-o", assembly, intermediate], env=env)
    if key in B.UNIT_SDATA:
        limit = next((int(f[2:]) for f in flags if re.fullmatch(r"-G\d+", f)), 0)
        assembly.write_text(B.append_external_sdata_metadata(
            assembly.read_text(), B.UNIT_SDATA[key], limit), encoding="utf-8")
    if key in B.UNIT_RODATA_SECTIONS:
        sections = iter(B.UNIT_RODATA_SECTIONS[key])
        assembly.write_text(re.sub(r"(?m)^[ \t]*\.rdata[ \t]*$",
                                   lambda _m: '\t.section %s, "a", @progbits' % next(sections, ".rodata"),
                                   assembly.read_text()), encoding="utf-8")
    if B.text_tail_splits(unit).get(Path(slot).stem):
        new = B.split_text_sections(assembly.read_text(), B.text_tail_splits(unit)[Path(slot).stem])
        if new is None:
            raise RuntimeError("failed canonical text-tail split")
        assembly.write_text(new, encoding="utf-8")
    output.unlink(missing_ok=True)
    command([sys.executable, B.maspsx_py(), *maspsx,
             "--gnu-as-path=" + str((ROOT / B.tool("as")).resolve()),
             *asflags, "-o", output, assembly], env=env)
    if not output.is_file() or not output.stat().st_size:
        raise RuntimeError("maspsx returned without producing an object")


def body_for_seed(slot_text, function, seed_text):
    stub = re.compile(r'INCLUDE_ASM\("[^"]+",\s*' + re.escape(function) + r'\);')
    # Apply audited ABI fixes to both compact and complete private seeds.
    if function == "func_800AEFC4":
        slot_text = slot_text.replace("extern u8 *func_8007767C(u8 *, u8 *);",
                                      "extern s32 *func_8007767C(u8 *, s32 *);")
        seed_text = seed_text.replace("extern u8 *func_8007767C(u8 *, u8 *);",
                                      "extern s32 *func_8007767C(u8 *, s32 *);")
        seed_text = seed_text.replace("func_8007767C(owner, self + 0x1C)",
                                      "func_8007767C(owner, (s32 *)(self + 0x1C))")
    elif function == "func_800B0DC0":
        seed_text = seed_text.replace("(void *)0, 0, -1", "0, 0, -1")
        declarations = ('extern void func_80079AA4(u8 *, s32, s32, s32, s32);\n'
                        'extern void func_800B17D0(u8 *, s32);')
        slot_text = slot_text.replace('#include "common.h"',
                                      '#include "common.h"\n' + declarations, 1)
        if '#include "common.h"' in seed_text and "extern void func_80079AA4" not in seed_text:
            seed_text = seed_text.replace('#include "common.h"',
                                          '#include "common.h"\n' + declarations, 1)
    if '#include "common.h"' in seed_text and seed_text.count("INCLUDE_ASM(") > 1:
        if stub.search(seed_text):
            raise ValueError("full-slot seed still contains the target ASM stub")
        clean = mask(seed_text)
        definition = re.search(r"(?m)^[^;{}\n]*\b" + re.escape(function) + r"\s*\([^;{}]*\)\s*\{",
                               clean)
        if definition is None:
            raise ValueError("target definition missing from full-slot seed")
        depth, end = 1, definition.end()
        while depth and end < len(clean):
            depth += (clean[end] == "{") - (clean[end] == "}")
            end += 1
        if depth:
            raise ValueError("unclosed target body in full-slot seed")
        prefix = seed_text.split('INCLUDE_ASM(', 1)[0]
        return seed_text, prefix + "\n" + seed_text[definition.start():end] + "\n"
    if len(stub.findall(slot_text)) != 1:
        raise ValueError("target must have one intact ASM stub in canonical source")
    full = stub.sub(seed_text, slot_text)
    # A compact source for the permuter: identical declarations/definition, no
    # other function bodies. Its compiled target must equal the full-slot one.
    prefix = slot_text.split('INCLUDE_ASM(', 1)[0]
    compact = prefix + "\n" + seed_text + "\n"
    return full, compact


def function_bytes(obj, function):
    symbols, relocations = object_symbols([str(obj)])
    if function not in symbols:
        raise RuntimeError(f"missing compiled symbol {function}")
    path, section, offset, size = symbols[function]
    raw = obj.with_name(obj.stem + "_" + section.lstrip(".") + ".bin")
    command([B.tool("objcopy"), "-O", "binary", "-j", section, obj, raw])
    data = raw.read_bytes()[offset:offset + size]
    rel = {x - offset for x in relocations.get((path, section), ()) if offset <= x < offset + size}
    return data, rel, offset


def retail_bytes(unit, function, slot_path):
    rows = {x["name"]: x for x in manifest(unit)}
    if function not in rows:
        raise ValueError(f"{function} absent from retail manifest")
    size = original_size(unit, function, slot_path)
    if size is None:
        raise ValueError(f"retail size unavailable for {function}")
    cfg = B.CONFIG[unit]
    image = (ROOT / cfg["target"]).read_bytes()
    if hashlib.sha1(image).hexdigest() != cfg["sha1"]:
        raise ValueError("retail SHA-1 does not match build manifest")
    offset = rows[function]["address"] - cfg["vram"] + cfg["file_base"]
    data = image[offset:offset + size]
    if len(data) != size:
        raise ValueError("retail function truncated")
    return data


def compare_object(obj, unit, function, slot_path):
    actual, rel, off = function_bytes(obj, function)
    expected = retail_bytes(unit, function, slot_path)
    diffs = compare_words(actual, expected, rel)
    return {"built_size": len(actual), "retail_size": len(expected),
            "differing_words": len(diffs), "differences": diffs[:16],
            "relocated_words": len(rel), "diagnostic_match": len(actual) == len(expected) and not diffs,
            "offset": off, "sha256": hashlib.sha256(actual).hexdigest()}


def assemble_target(unit, slot, function, directory, offset):
    asm = ROOT / "asm/us" / unit / "nonmatchings" / Path(slot).stem / (function + ".s")
    text = asm.read_text(encoding="utf-8")
    text = re.sub(r"(?m)^\s*jlabel\s+(\.L\w+)\s*$", r"\1:", text)
    source = directory / "retail.s"
    source.write_text('.include "macro.inc"\n.set noreorder\n.set noat\n.text\n' + text,
                      encoding="utf-8")
    unshifted = directory / "retail.o"
    target = directory / "target.o"
    command([B.tool("as"), *B.AS_FLAGS, "-I", ROOT / "include", "-o", unshifted, source])
    # Only section metadata changes. Scored instruction and relocation bytes are
    # the assembled retail bytes, with the function's candidate text offset.
    command([B.tool("objcopy"), "--change-section-vma", f".text={hex(offset)}",
             unshifted, target])
    return target


def prepare(unit, function, seed, directory):
    definitions, stubs, _ = source_functions(unit)
    if function not in stubs:
        raise ValueError(f"{unit}:{function} has no ASM stub to replace")
    slot_path = ROOT / stubs[function]
    slot = slot_path.name
    if B.UNIT_CXX.get(f"{unit}/{slot}"):
        raise ValueError("the installed permuter C parser cannot safely search C++ slots")
    slot_sha = hashlib.sha256(slot_path.read_bytes()).hexdigest()
    seed_sha = hashlib.sha256(seed.read_bytes()).hexdigest()
    full, compact = body_for_seed(slot_path.read_text(encoding="utf-8"), function,
                                  seed.read_text(encoding="utf-8"))
    directory.mkdir(parents=True, exist_ok=False)
    full_path = directory / "full_slot.c"
    base_path = directory / "base.c"
    full_path.write_text(full, encoding="utf-8")
    base_path.write_text(compact, encoding="utf-8")
    full_obj = directory / "full_slot.o"
    compact_obj = directory / "base.o"
    compile_source(full_path, full_obj, unit, slot)
    compile_source(base_path, compact_obj, unit, slot)
    full_data, full_rel, _ = function_bytes(full_obj, function)
    base_data, base_rel, base_offset = function_bytes(compact_obj, function)
    if len(full_data) != len(base_data) or full_rel != base_rel or compare_words(
            base_data, full_data, full_rel):
        raise RuntimeError("function-only seed instructions/relocations differ from full-slot compile")
    siblings = [name for name, entry in definitions.items() if entry["source"] == stubs[function]
                and entry["category"] != "cxx_alias"]
    sibling_rows = {name: compare_object(full_obj, unit, name, slot_path) for name in siblings}
    if any(not row["diagnostic_match"] for row in sibling_rows.values()):
        raise RuntimeError("private full-slot baseline broke an existing C sibling")
    target = assemble_target(unit, slot, function, directory, base_offset)
    objdump = (ROOT / B.tool("objdump")).resolve()
    command_line = f'"{objdump.as_posix()}" -drz --disassemble={function}'
    sys.path.insert(0, str(PERMUTER))
    from src.scorer import Scorer
    scorer = Scorer(str(target), stack_differences=True, algorithm="difflib",
                    debug_mode=False, ign_branch_targets=False,
                    objdump_command=command_line)
    score = scorer.score(str(compact_obj))[0]
    settings = (f'func_name = "{function}"\ncompiler_type = "gcc"\n'
                f'objdump_command = "{command_line.replace(chr(34), chr(92) + chr(34))}"\n')
    (directory / "settings.toml").write_text(settings, encoding="utf-8")
    # Permuter compiles temp sources through Git Bash. Use the exact Python
    # executable supplied by this invocation, the same profile and no cache.
    bridge = ("import sys\nfrom pathlib import Path\n"
              f"sys.path.insert(0, {str(ROOT / 'tools')!r})\n"
              "from permuter_batch import compile_source\n"
              f"compile_source(Path(sys.argv[1]), Path(sys.argv[3]), {unit!r}, {slot!r})\n")
    (directory / "compile.py").write_text(bridge, encoding="utf-8")
    root_unix = "/" + ROOT.as_posix().replace(":", "", 1).lower()[0] + ROOT.as_posix()[2:]
    py_path = Path(sys.executable).as_posix()
    py_unix = "/" + py_path[0].lower() + py_path[2:]
    (directory / "compile.sh").write_text(
        '#!/usr/bin/env bash\nset -e\nexport MSYS2_ARG_CONV_EXCL="*"\n'
        f'cd "{root_unix}"\nexec "{py_unix}" "{(directory / "compile.py").as_posix()}" "$@"\n',
        encoding="utf-8", newline="\n")
    return {"unit": unit, "function": function, "slot": stubs[function],
            "slot_sha256": slot_sha, "seed": seed.relative_to(ROOT).as_posix(),
            "seed_sha256": seed_sha, "toolchain": canonical_toolchain(unit, slot)[:3],
            "full_slot": compare_object(full_obj, unit, function, slot_path),
            "sibling_count": len(sibling_rows), "siblings_all_match": True,
            "compact_equals_full": True, "score": score, "workdir": str(directory)}


def run_permuter(cmd, env, timeout, log_path, max_iterations=None):
    """Bound the process tree and retain an approximate CPU accounting."""
    try:
        import psutil
    except ImportError:
        psutil = None
    started = time.perf_counter()
    cpu_seen = {}
    timed_out = False
    interrupted = False
    iteration_limited = False
    with log_path.open("w", encoding="utf-8") as log:
        process = subprocess.Popen([str(x) for x in cmd], cwd=log_path.parent,
                                   env=env, stdout=log, stderr=subprocess.STDOUT)
        root_process = psutil.Process(process.pid) if psutil else None
        try:
            while process.poll() is None:
                if root_process:
                    try:
                        children = [root_process, *root_process.children(recursive=True)]
                        for child in children:
                            try:
                                times = child.cpu_times()
                                cpu_seen[child.pid] = max(cpu_seen.get(child.pid, 0.0),
                                                          times.user + times.system)
                            except (psutil.NoSuchProcess, psutil.AccessDenied):
                                pass
                    except (psutil.NoSuchProcess, psutil.AccessDenied):
                        pass
                if time.perf_counter() - started >= timeout:
                    timed_out = True
                    break
                if max_iterations is not None and log_path.is_file():
                    observed = [int(x) for x in re.findall(
                        r"iteration (\d+)", log_path.read_text(encoding="utf-8", errors="replace"))]
                    if observed and max(observed) >= max_iterations:
                        iteration_limited = True
                        break
                time.sleep(0.1)
        except KeyboardInterrupt:
            interrupted = True
        if timed_out or interrupted or iteration_limited:
            # Terminate only the spawned search tree; never kill unrelated jobs.
            subprocess.run(["taskkill.exe", "/T", "/F", "/PID", str(process.pid)],
                           capture_output=True, text=True)
            if process.poll() is None:
                process.kill()
        rc = process.wait()
    observed = [int(x) for x in re.findall(
        r"iteration (\d+)", log_path.read_text(encoding="utf-8", errors="replace"))]
    return {"returncode": rc, "timed_out": timed_out, "interrupted": interrupted,
            "iteration_limited": iteration_limited, "iterations_observed": max(observed, default=0),
            "wall_seconds": round(time.perf_counter() - started, 3),
            "cpu_seconds_observed": round(sum(cpu_seen.values()), 3) if psutil else None,
            "cpu_note": "sampled process-tree CPU; short-lived compiler children may be missed" if psutil
                        else "psutil unavailable; process-tree CPU not measured",
            "log": str(log_path)}


def best_outputs(report):
    for row in report["targets"]:
        workdir = Path(row["workdir"])
        candidates = []
        for directory in workdir.glob("output-*-*"):
            score_file = directory / "score.txt"
            if score_file.is_file():
                try:
                    candidates.append((int(score_file.read_text().strip()), directory))
                except ValueError:
                    pass
        best = min(candidates, default=None)
        row["best_score"] = min(row["score"], best[0]) if best else row["score"]
        row["best_candidate"] = str(best[1] / "source.c") if best and best[0] <= row["score"] else None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("targets", nargs="+", metavar="UNIT:FUNCTION=SEED_PATH")
    parser.add_argument("--run", action="store_true", help="execute bounded search after preparation")
    parser.add_argument("--debug", action="store_true", help="run permuter's compile/parse baseline only")
    parser.add_argument("--timeout", type=int, default=60, help="search wall seconds, maximum 120")
    parser.add_argument("--jobs", type=int, default=2, help="search worker count, 1 or 2")
    parser.add_argument("--max-iterations", type=int, default=10,
                        help="stop after at most this many observed permutations (default 10)")
    args = parser.parse_args()
    if not 1 <= args.timeout <= 120 or args.jobs not in (1, 2) or not 1 <= args.max_iterations <= 1000:
        parser.error("timeout must be 1..120 seconds, jobs 1 or 2, iterations 1..1000")
    parsed = []
    sdk = sdk_symbols()
    for spec in args.targets:
        if "=" not in spec or ":" not in spec.split("=", 1)[0]:
            parser.error("each target must be UNIT:FUNCTION=SEED_PATH")
        target, path = spec.split("=", 1)
        unit, function = target.split(":", 1)
        if unit not in UNITS:
            parser.error(f"unknown source unit: {unit}")
        if not re.fullmatch(r"func_[0-9A-Fa-f]{8}", function):
            parser.error(f"invalid function name: {function}")
        if (unit, function) in sdk:
            parser.error(f"SDK symbol is retained as assembly: {unit}:{function}")
        seed = (ROOT / path).resolve()
        if not seed.is_file() or not seed.is_relative_to(ROOT):
            parser.error(f"seed must be a workspace file: {path}")
        parsed.append((unit, function, seed))
    OUT.mkdir(parents=True, exist_ok=True)
    stamp = time.strftime("%Y%m%dT%H%M%SZ", time.gmtime()) + f"-{os.getpid()}"
    batch = OUT / stamp
    batch.mkdir()
    report = {"batch": str(batch), "run_requested": args.run, "targets": [],
              "acceptance": "diagnostic only; no source landing or linked-unit credit"}
    try:
        for unit, function, seed in parsed:
            row = prepare(unit, function, seed, batch / f"{unit}_{function}")
            report["targets"].append(row)
        if args.run or args.debug:
            bash = Path(r"C:\Program Files\Git\bin\bash.exe")
            if not bash.is_file():
                raise RuntimeError("Git Bash not installed at expected native path")
            python = ROOT / ".venv-permuter/Scripts/python.exe"
            if not python.is_file():
                raise RuntimeError("native permuter venv Python unavailable")
            launcher = batch / "launch.py"
            launcher.write_text(
                "import subprocess, sys\nfrom pathlib import Path\n"
                f"sys.path.insert(0, {str(ROOT / 'tools')!r})\n"
                f"sys.path.insert(0, {str(PERMUTER)!r})\n"
                "import build_dra as B\nimport src.main as M\n"
                "def native_preprocess(filename):\n"
                "    cmd = [B.cpp_bin(), *B.CPP_FLAGS, '-DPERMUTER', filename]\n"
                "    return subprocess.check_output(cmd, cwd=B.ROOT, text=True)\n"
                "M.preprocess = native_preprocess\n"
                "if __name__ == '__main__':\n    M.main()\n", encoding="utf-8")
            cmd = [python, launcher, "--stack-diffs", "--no-ignore-branch-targets",
                   "--stop-on-zero", "--best-only", "-j", str(args.jobs),
                   *[x["workdir"] for x in report["targets"]]]
            env = dict(os.environ)
            env["PATH"] = str(bash.parent) + os.pathsep + env.get("PATH", "")
            env["PYTHONUNBUFFERED"] = "1"
            # The installed permuter hardcodes `cpp` for its AST input. A
            # private launcher uses the same native preprocessor as the build.
            for row in report["targets"]:
                debug_log = batch / (row["function"] + "_debug.log")
                debug_cmd = cmd[:2] + ["--debug"] + cmd[2:-len(report["targets"])] + [row["workdir"]]
                row["debug"] = run_permuter(debug_cmd, env, min(args.timeout, 20), debug_log)
                log_text = debug_log.read_text(encoding="utf-8", errors="replace")
                scores = [int(x) for x in re.findall(r"base score = (\d+)", log_text)]
                row["debug"]["reported_scores"] = scores
                compiled = batch / "debug_compiled_object.o"
                if not compiled.is_file():
                    raise RuntimeError("permuter debug produced no compiled object")
                debug_data, debug_reloc, _ = function_bytes(compiled, row["function"])
                base_data, base_reloc, _ = function_bytes(Path(row["workdir"]) / "base.o", row["function"])
                same = len(debug_data) == len(base_data) and debug_reloc == base_reloc \
                    and not compare_words(debug_data, base_data, base_reloc)
                row["debug"]["instructions_equal_to_independent_baseline"] = same
                if row["debug"]["returncode"] != 0 or scores != [row["score"]] or not same:
                    raise RuntimeError(f"permuter baseline disagrees with measured native object for {row['function']}")
            if args.run:
                report["search"] = run_permuter(cmd, env, args.timeout, batch / "search.log",
                                                args.max_iterations)
                best_outputs(report)
    except BaseException as exc:
        report["error"] = repr(exc)
        raise
    finally:
        (batch / "report.json").write_text(json.dumps(report, indent=2, default=str) + "\n",
                                           encoding="utf-8")
        print(json.dumps(report, indent=2, default=str))


if __name__ == "__main__":
    main()
