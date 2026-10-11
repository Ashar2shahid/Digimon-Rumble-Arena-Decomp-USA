"""Preserve SDK name-identification evidence without choosing ambiguous aliases."""
from collections import defaultdict
import json
from source_inventory import ROOT, sdk_symbols


def main():
    excluded = sdk_symbols()
    entries, archives, errors = defaultdict(list), set(), []
    for unit in ("main", "movie"):
        path = ROOT / "analysis/sdk-identification" / f"{unit}.json"
        report = json.loads(path.read_text())
        archives.add(report["library_archive_sha256"])
        errors.extend(dict(unit=unit, **error) for error in report["parser_errors"])
        for hit in report["hits"]:
            entries[(unit, hit["function"])].append(hit)
    result = []
    for (unit, function), hits in sorted(entries.items()):
        names = sorted({name for hit in hits for name in hit["names"]})
        result.append(dict(unit=unit, function=function, candidate_names=names,
                           ambiguous_name=len(names) != 1, currently_classified_sdk=(unit, function) in excluded,
                           evidence=hits))
    output = dict(library_archive_sha256=sorted(archives), symbols=result, parser_errors=errors,
                  limitations=["Names identify exact non-relocated symbol windows, not original game source names.",
                               "Identical code may have several names; no aliases or exclusions are added automatically.",
                               "Window size may include private helper code after a public entry.",
                               "Relocated instruction and pointer values need separate review."])
    (ROOT / "config/us/sdk_symbols.json").write_text(json.dumps(output, indent=2) + "\n")
    print(f"SDK name evidence: {len(result)} addresses; {sum(e['ambiguous_name'] for e in result)} ambiguous names")


if __name__ == "__main__":
    main()
