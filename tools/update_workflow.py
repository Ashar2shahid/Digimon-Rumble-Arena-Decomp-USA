"""Generate difficult-function records and README metrics from canonical progress."""
import argparse
import hashlib
import json
from pathlib import Path, PurePosixPath
import re

from source_inventory import ROOT

BEGIN = "<!-- BEGIN GENERATED PROGRESS -->"
END = "<!-- END GENERATED PROGRESS -->"


def report_json(path):
    text = path.read_text()
    # A launcher may print a warning before probe_slot's single JSON document.
    # Reject trailing diagnostics or an incomplete document.
    decoder = json.JSONDecoder()
    for index, character in enumerate(text):
        if character != "{":
            continue
        try:
            report, end = decoder.raw_decode(text[index:])
        except json.JSONDecodeError:
            continue
        if isinstance(report, dict) and not text[index + end:].strip():
            return report
    raise ValueError("Probe report has no complete final JSON document")


def snapshot_inputs_current(root, checkpoint, metadata):
    inputs = metadata.get("copied_inputs_sha256")
    if not isinstance(inputs, dict) or metadata.get("recorded_inputs") != len(inputs):
        return False
    for relative, expected in inputs.items():
        if (not isinstance(relative, str) or not relative or "\\" in relative or ":" in relative
                or PurePosixPath(relative).is_absolute() or any(part in ("", ".", "..") for part in relative.split("/"))
                or not isinstance(expected, str) or not re.fullmatch(r"[0-9a-f]{64}", expected)):
            return False
        for base in (root, checkpoint):
            path = base / relative
            if not path.is_file() or path.is_symlink():
                return False
            if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
                return False
    return True


def matching_checkpoint(progress, root=ROOT):
    """Select a checkpoint containing the exact saved canonical progress."""
    if not progress.get("all_modules_verified") or progress.get("inventory_problems"):
        raise ValueError("Refresh verified progress and save a matching checkpoint first")
    saved = root / "config/us/progress.json"
    saved_bytes = saved.read_bytes()
    if json.loads(saved_bytes) != progress:
        raise ValueError("Progress changed during workflow update")
    for directory in sorted((root / "analysis/checkpoints").glob("*"), reverse=True):
        metadata_path = directory / "checkpoint.json"
        checkpoint_progress = directory / "progress.json"
        if not metadata_path.is_file() or not checkpoint_progress.is_file():
            continue
        metadata = json.loads(metadata_path.read_text())
        if (metadata.get("game_functions") != progress["game_manifest_functions"]
                or metadata.get("unconstrained_source") != progress["verified_unconstrained_source"]
                or metadata.get("recorded_inputs") != len(metadata.get("copied_inputs_sha256", {}))):
            continue
        if checkpoint_progress.read_bytes() == saved_bytes and snapshot_inputs_current(root, directory, metadata):
            return directory, metadata
    raise ValueError("Refresh verified progress and save a matching checkpoint first")


def measured_words(attempt, unit, function, source_slot, root=ROOT):
    """Accept a completed private comparison, including a nonmatching exit 1."""
    if attempt.get("source_candidate_valid") is False:
        return None
    if attempt.get("exit_code") not in (0, 1):
        return None
    relative = attempt.get("report")
    if not isinstance(relative, str):
        return None
    path = (root / relative).resolve()
    scratch = (root / "analysis/scratch" / unit / function).resolve()
    if not path.is_relative_to(scratch):
        return None
    try:
        report = report_json(path)
        if (report.get("unit") != unit or report.get("source") != source_slot
                or report.get("source_sha256") != attempt.get("source_sha256")):
            return None
        result = next(entry for entry in report["results"] if entry["function"] == function)
        words = result.get("differing_words")
        if (not isinstance(words, int) or isinstance(words, bool) or words < 0
                or result.get("built_size") != result.get("retail_size")):
            return None
        return words
    except (OSError, ValueError, KeyError, StopIteration, TypeError):
        return None


def difficult_rows(worklist):
    rows = []
    seen = set()
    for candidate in worklist["candidates"]:
        failed = [entry for entry in candidate["attempts"] if entry.get("outcome") not in ("accepted", "matched", "verified")]
        if candidate["manifest_kind"] != "func":
            continue
        unit, function = candidate["unit"], candidate["function"]
        directory = ROOT / "analysis/scratch" / unit / function
        state_path = directory / "session.json"
        state = json.loads(state_path.read_text()) if state_path.exists() else {"probes": [], "cycle": 0}
        target = state.get("target")
        if target and (target.get("unit"), target.get("function"), target.get("source")) != (
                unit, function, candidate["source_slot"]):
            state = {"probes": [], "cycle": 0}
        capped = sum(entry.get("cycle") == state.get("cycle", 0) for entry in state["probes"]) >= 10
        if not failed and not capped:
            continue
        observed = [value for attempt in state["probes"]
                    if (value := measured_words(attempt, unit, function, candidate["source_slot"], ROOT)) is not None]
        seed = state.get("seed")
        if seed is None:
            seed = next((entry["draft"] for entry in reversed(failed) if isinstance(entry.get("draft"), str)), None)
        rows.append(dict(unit=unit, function=function, source_slot=candidate["source_slot"],
                         manual_probe_count=len(state["probes"]), historical_summary_entries=len(failed),
                         best_measured_differing_words=min(observed) if observed else None,
                         reason=failed[-1].get("reason", failed[-1].get("outcome", "Unresolved")) if failed else "Ten manual probes reached; calibrated CPU search pending",
                         seed=seed, logic_review="required before permutation", requeue_on="new relevant learning or profile/boundary evidence"))
        seen.add((unit, function))
    scratch = ROOT / "analysis/scratch"
    for state_path in sorted(scratch.glob("*/func_*/session.json")):
        state = json.loads(state_path.read_text())
        target = state.get("target", {})
        unit, function = target.get("unit"), target.get("function")
        if ((unit, function) in seen or target.get("calibration")
                or sum(entry.get("cycle") == state.get("cycle", 0) for entry in state.get("probes", [])) < 10):
            continue
        source = target.get("source")
        if not isinstance(source, str) or not unit or not function:
            continue
        observed = [value for attempt in state["probes"]
                    if (value := measured_words(attempt, unit, function, source, ROOT)) is not None]
        rows.append(dict(unit=unit, function=function, source_slot=source,
                         manual_probe_count=len(state["probes"]), historical_summary_entries=0,
                         best_measured_differing_words=min(observed) if observed else None,
                         reason="Capped scratch session absent current worklist; review status",
                         seed=state.get("seed"), logic_review="required before permutation",
                         requeue_on="new relevant learning or profile/boundary evidence"))
    return rows


def generated_progress(progress, metadata, checkpoint):
    categories = progress["source_categories"]
    lines = [BEGIN, "### Verified checkpoint", "",
             f"All **14 code units** passed complete-byte and source-placement checks. Saved checkpoint: `{checkpoint}`.",
             f"All **{metadata['recorded_inputs']:,} recorded build inputs** were copied and hash checked.", "",
             "| Game function representation | Count |", "| --- | ---: |"]
    for category, label in (("ordinary_c", "Ordinary C"), ("empty_c", "Empty C"), ("cxx_alias", "C++ implementations"), ("assisted_c", "C with assembly/register constraints"), ("assembly", "Assembly placeholders")):
        lines.append(f"| {label} | {categories.get(category, 0):,} |")
    lines.extend([f"| **Provisional game functions** | **{progress['game_manifest_functions']:,}** |", "",
                  f"Source without assembly/register constraints: **{progress['verified_unconstrained_source']:,} functions ({progress['verified_unconstrained_percent']:.4f}% by function count)**.",
                  f"PsyQ: **{progress['sdk_manifest_entries']} entries**, excluded from game-source progress and retained as symbolized assembly.", "",
                  "Counts come from `config/us/progress.json`. They remain provisional: function boundaries, source semantics, original-object compiler profiles, data/relocations and modified/runtime builds still require review.",
                  "Some compiler ranges isolate single functions; byte identity does not certify their original object boundaries or compiler settings. See `config/us/compiler_profiles.json`.", "",
                  "Read [PLAN.md](PLAN.md) to resume. [Codegen model](docs/CODEGEN_MODEL.md) and [searchable learnings](docs/DECOMPILATION_LEARNINGS.md) record the evidence. Private probes and permuter scores earn no source credit before the complete linked gate.", END])
    return "\n".join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--save", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)
    progress = json.loads((ROOT / "config/us/progress.json").read_text())
    try:
        directory, metadata = matching_checkpoint(progress)
    except ValueError as error:
        parser.exit(2, str(error) + "\n")
    generated = generated_progress(progress, metadata, directory.relative_to(ROOT).as_posix())
    readme = ROOT / "README.md"
    original = readme.read_text()
    if BEGIN in original:
        updated = re.sub(re.escape(BEGIN) + r"[\s\S]*?" + re.escape(END), lambda match: generated, original, count=1)
    else:
        start = original.index("### Verified checkpoint")
        end = original.index("## Build and inspect", start)
        updated = original[:start] + generated + "\n\n" + original[end:]
    worklist = json.loads((ROOT / "config/us/worklist.json").read_text())
    rows = difficult_rows(worklist)
    if args.save:
        readme.write_text(updated)
        (ROOT / "config/us/difficult_functions.json").write_text(json.dumps(dict(functions=rows, note="Historical summary counts are not actual compiler-attempt counts; measured probes use session.json. Seeds still require logic/type review."), indent=2) + "\n")
        lines = ["# unit:function\tmanual_probes\thistorical_summaries\tbest_word_diff\treason\tseed"]
        for row in rows:
            reason = str(row["reason"]).replace("\n", " ").replace("\t", " ")
            lines.append(f"{row['unit']}:{row['function']}\t{row['manual_probe_count']}\t{row['historical_summary_entries']}\t{row['best_measured_differing_words']}\t{reason}\t{row['seed'] or '-'}")
        (ROOT / "tools/difficult_functions").write_text("\n".join(lines) + "\n")
    if args.check and original != updated:
        parser.exit(1, "README progress differs from its canonical progress/checkpoint inputs\n")
    print(f"Canonical progress {progress['verified_unconstrained_source']}/{progress['game_manifest_functions']}; {len(rows)} unresolved functions with attempt evidence")


if __name__ == "__main__":
    main()
