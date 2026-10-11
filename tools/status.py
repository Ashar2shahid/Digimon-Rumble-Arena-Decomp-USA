"""Report verified C separately from provisional disassembly and automated drafts."""
import argparse
import csv
import hashlib
import json
from pathlib import Path

from build import inputs_fingerprint


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--save", action="store_true", help="save a reviewable progress snapshot to config/us/progress.json")
    args = parser.parse_args()
    config = json.loads(Path("config/us/project.json").read_text())
    results = []
    for module in config["modules"]:
        name = module["name"]
        directory = Path("analysis/us") / name
        inventory = directory / "functions.csv"
        functions = list(csv.DictReader(inventory.open())) if inventory.exists() else []
        verification = Path("build/us") / name / "verification.json"
        result = dict(module=name, provisional_functions=len(functions), current_verified_build=False,
                      configured_text_bytes=int(module["text_end"], 0) - int(module["text_start"], 0),
                      recovered_c_functions=0, recovered_c_bytes=0)
        if verification.exists():
            evidence = json.loads(verification.read_text())
            binary = Path("build/us") / name / Path(module["path"]).name
            fresh = evidence.get("inputs_sha256") == inputs_fingerprint(module, config, evidence.get("assembly_only", False))
            valid = binary.exists() and hashlib.sha1(binary.read_bytes()).hexdigest() == module["sha1"]
            result["current_verified_build"] = fresh and valid
            if fresh and valid:
                for key in ("recovered_c_functions", "recovered_c_bytes", "sha1", "functions"):
                    result[key] = evidence[key]
        draft = directory / "drafts.c"
        result["draft_failure_markers"] = draft.read_text().count("Decompilation failure in function") if draft.exists() else None
        results.append(result)
        state = "verified" if result["current_verified_build"] else "build required"
        print(f"{name:6} {state:14} C {result['recovered_c_functions']:4}/{len(functions):4} functions; drafts failed {result['draft_failure_markers']}")
    text = sum(r["configured_text_bytes"] for r in results)
    c_bytes = sum(r["recovered_c_bytes"] for r in results)
    snapshot = dict(all_modules_verified=all(r["current_verified_build"] for r in results),
                    provisional_functions=sum(r["provisional_functions"] for r in results),
                    recovered_c_functions=sum(r["recovered_c_functions"] for r in results),
                    configured_text_bytes=text, recovered_c_bytes=c_bytes,
                    c_percent_of_configured_text=round(c_bytes * 100 / text, 4), modules=results)
    print(f"Total: {snapshot['recovered_c_functions']}/{snapshot['provisional_functions']} C functions; {c_bytes}/{text} bytes ({snapshot['c_percent_of_configured_text']}%)")
    if args.save:
        Path("config/us/progress.json").write_text(json.dumps(snapshot, indent=2) + "\n")


if __name__ == "__main__":
    main()
