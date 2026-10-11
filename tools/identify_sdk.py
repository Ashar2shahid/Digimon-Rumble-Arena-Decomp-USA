"""Identify candidate SDK symbols using held libraries and exact non-relocated words.

The LIB/LNK reader is adapted from the older project's CC0 scratch tooling.
Results are evidence for review; this tool does not change source or exclusions.
"""
import argparse
import hashlib
import io
import json
from pathlib import Path
import struct
import zipfile

from psyq_format import parse_lib, parse_sections
from source_inventory import ROOT, manifest
import build_dra


def library_functions(path):
    _, modules = parse_lib(path)
    data = path.read_bytes()
    for module, _, begin, end in modules:
        records, version, _ = parse_sections(data[begin:end], 0)
        if version != 2:
            raise ValueError(f"Unsupported object version {version}: {path.name}/{module}")
        codes, patches, names, headers = {}, {}, {}, {}
        current, block_start = None, 0
        for kind, value in records:
            if kind == "LNKHeader":
                headers[value[0]] = value[2]
            elif kind == "SectionSwitch":
                current = value
            elif kind == "Code":
                block_start = len(codes.get(current, b""))
                codes[current] = codes.get(current, b"") + value
            elif kind == "Patch":
                patches.setdefault(current, set()).add(block_start + (value[1] & ~3))
            elif kind in ("FunctionStart", "XDEF", "LocalSymbol"):
                sid, offset, name = value
                names.setdefault(sid, {}).setdefault(offset, set()).add(name)
        for sid, code in codes.items():
            if headers.get(sid) != ".text":
                continue
            starts = sorted(names.get(sid, {}))
            for index, offset in enumerate(starts):
                end = starts[index + 1] if index + 1 < len(starts) else len(code)
                body = code[offset:end]
                if len(body) < 64 or len(body) % 4:
                    continue
                relocated = {p - offset for p in patches.get(sid, ()) if offset <= p < end}
                checks = [(p, body[p:p + 4]) for p in range(0, len(body), 4) if p not in relocated]
                if len(checks) < 16:
                    continue
                yield dict(names=sorted(names[sid][offset]), library=path.name, module=module,
                           size=len(body), checks=checks, relocated_words=len(relocated), section_offset=offset,
                           text_size=len(code), text_checks=[(p, code[p:p + 4]) for p in range(0, len(code), 4) if p not in patches.get(sid, ())])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("library_zip", type=Path)
    parser.add_argument("--unit", default="movie", choices=build_dra.UNITS)
    args = parser.parse_args()
    directory = ROOT / "analysis/sdk-identification"
    directory.mkdir(parents=True, exist_ok=True)
    archive_bytes = args.library_zip.read_bytes()
    archive_sha256 = hashlib.sha256(archive_bytes).hexdigest()
    libraries = directory / "libraries" / archive_sha256
    libraries.mkdir(parents=True, exist_ok=True)
    # Only known leaf .LIB files are written under the local analysis directory.
    extracted, leaves = [], set()
    with zipfile.ZipFile(io.BytesIO(archive_bytes)) as archive:
        for name in archive.namelist():
            if name.upper().endswith(".LIB"):
                leaf = Path(name.replace("\\", "/")).name
                if leaf.lower() in leaves:
                    raise ValueError(f"Duplicate library leaf in ZIP: {leaf}")
                leaves.add(leaf.lower())
                path = libraries / leaf
                path.write_bytes(archive.read(name))
                extracted.append(path)
    functions, errors = [], []
    for path in sorted(extracted):
        try:
            functions.extend(library_functions(path))
        except (ValueError, IndexError, struct.error, AssertionError) as error:
            errors.append(dict(library=path.name, error=str(error)))
    cfg = build_dra.CONFIG[args.unit]
    binary = (ROOT / cfg["target"]).read_bytes()
    if hashlib.sha1(binary).hexdigest() != cfg["sha1"]:
        raise ValueError("Incorrect target revision")
    hits, modules = [], {}
    for row in manifest(args.unit):
        offset = row["address"] - cfg["vram"] + cfg["file_base"]
        for candidate in functions:
            if offset < 0 or offset + candidate["size"] > len(binary):
                continue
            if all(binary[offset + p:offset + p + 4] == word for p, word in candidate["checks"]):
                hits.append(dict(unit=args.unit, function=row["name"], address=hex(row["address"]),
                                 names=candidate["names"], library=candidate["library"], module=candidate["module"],
                                 size=candidate["size"], verified_nonrelocated_words=len(candidate["checks"]),
                                 relocated_words=candidate["relocated_words"]))
                base = row["address"] - candidate["section_offset"]
                begin = offset - candidate["section_offset"]
                if begin >= 0 and begin + candidate["text_size"] <= len(binary) and all(binary[begin+p:begin+p+4] == word for p,word in candidate["text_checks"]):
                    key = (candidate["library"], candidate["module"], base)
                    modules[key] = dict(library=key[0], module=key[1], text_start=hex(base),
                                        text_end=hex(base + candidate["text_size"]), text_size=candidate["text_size"],
                                        verified_nonrelocated_words=len(candidate["text_checks"]))
    report = dict(unit=args.unit, input_sha1=cfg["sha1"], library_archive_sha256=archive_sha256,
                  candidate_functions=len(functions), hits=hits, complete_text_modules=list(modules.values()), parser_errors=errors,
                  method="complete library-symbol window; exact unchanged words outside LNK PATCH word offsets; at least 16 unchanged words",
                  limitations=["relocated word values and symbol identities still require review",
                               "identical implementations can have multiple library names",
                               "a match is identification evidence, not a source-recovery percentage or an automatic SDK exclusion"])
    (directory / f"{args.unit}.json").write_text(json.dumps(report, indent=2) + "\n")
    print(f"{args.unit}: {len(hits)} candidate SDK identifications from {len(functions)} library functions; {len(errors)} parser errors")
    for hit in hits:
        print(f"{hit['function']} -> {hit['library']}/{hit['module']}: {','.join(hit['names'])} ({hit['size']} bytes)")


if __name__ == "__main__":
    main()
