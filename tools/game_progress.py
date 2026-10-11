"""Report game source coverage separately from PsyQ and assembly constraints."""
import argparse
from collections import Counter
import json
import sys

from source_inventory import ROOT, UNITS, manifest, sdk_symbols, source_functions
from verify import current_verification


def report():
    excluded = sdk_symbols()
    units = []
    all_categories = Counter()
    problems = []
    for unit in UNITS:
        definitions, stubs, duplicates = source_functions(unit)
        problems.extend(f"{unit}: duplicate definition {name}" for name in duplicates)
        problems.extend(f"{unit}: both C and assembly stub {name}" for name in definitions.keys() & stubs.keys())
        rows = manifest(unit)
        known = {r["name"] for r in rows}
        problems.extend(f"{unit}: definition absent from manifest {name}" for name in definitions.keys() - known)
        categories, sdk_kinds, game_kinds = Counter(), Counter(), Counter()
        functions = []
        for row in rows:
            name = row["name"]
            if (unit, name) in excluded:
                sdk_kinds[row["kind"]] += 1
                if name in definitions:
                    problems.append(f"{unit}: SDK source definition still present {name}")
                continue
            game_kinds[row["kind"]] += 1
            if row["kind"] != "func":
                continue
            entry = definitions.get(name)
            category = entry["category"] if entry else "assembly" if name in stubs else "unresolved"
            categories[category] += 1
            functions.append(dict(name=name, address=hex(row["address"]), category=category,
                                  source=entry["source"] if entry else stubs.get(name)))
        state = current_verification(unit)
        source_count = sum(categories[c] for c in ("ordinary_c", "empty_c", "assisted_c", "source_hack_c", "cxx_alias"))
        unconstrained = categories["ordinary_c"] + categories["empty_c"] + categories["cxx_alias"]
        result = dict(unit=unit, current_verified_build=state["current_verified_build"],
                      verification_reason=state["reason"], game_manifest_functions=sum(categories.values()),
                      source_representations=source_count, unconstrained_source_representations=unconstrained,
                      verified_source_representations=source_count if state["current_verified_build"] else 0,
                      verified_unconstrained_source=unconstrained if state["current_verified_build"] else 0,
                      categories=dict(categories), sdk_manifest_kinds=dict(sdk_kinds),
                      other_game_manifest_kinds={k: v for k, v in game_kinds.items() if k != "func"}, functions=functions)
        units.append(result)
        all_categories.update(categories)
        status = "verified" if state["current_verified_build"] else "build required"
        print(f"{unit:6} {status:14} game source {source_count:4}/{sum(categories.values()):4}; "
              f"asm {categories['assembly']:4}; assisted/hack {categories['assisted_c']:3}/{categories['source_hack_c']}; "
              f"SDK func/asm/data {sdk_kinds['func']}/{sdk_kinds['asm']}/{sdk_kinds['data']}")
    total = sum(all_categories.values())
    verified = sum(u["verified_unconstrained_source"] for u in units)
    snapshot = dict(all_modules_verified=all(u["current_verified_build"] for u in units),
                    denominator="non-SDK manifest rows of kind func; provisional boundaries",
                    game_manifest_functions=total, source_categories=dict(all_categories),
                    verified_unconstrained_source=verified,
                    verified_unconstrained_percent=round(100 * verified / total, 4) if total else 0,
                    sdk_manifest_entries=sum(sum(u["sdk_manifest_kinds"].values()) for u in units),
                    inventory_problems=problems, units=units,
                    limitations=["source bodies are lexical classifications; complete output and symbol placement gate verification",
                                 "empty functions and C++ aliases are reported separately",
                                 "assisted C retains inline assembly or register constraints and is not unconstrained source credit",
                                 "explicitly documented register-forcing/uninitialized-variable source tricks are a separate category; other semantic issues still require review",
                                 "non-func game entries and opaque data require inventory review; 100% of this denominator alone is not project completion",
                                 "matching retail output does not establish relocatable or runtime-modified builds"])
    print(f"Game denominator: {total}; verified unconstrained source: {verified} ({snapshot['verified_unconstrained_percent']}%); SDK excluded: {snapshot['sdk_manifest_entries']} entries")
    for problem in problems:
        print(f"Inventory review: {problem}")
    return snapshot


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--save", action="store_true")
    parser.add_argument("--require-verified", action="store_true")
    args = parser.parse_args()
    snapshot = report()
    if args.save:
        (ROOT / "config/us/progress.json").write_text(json.dumps(snapshot, indent=2) + "\n")
    return 1 if args.require_verified and (not snapshot["all_modules_verified"] or snapshot["inventory_problems"]) else 0


if __name__ == "__main__":
    sys.exit(main())
