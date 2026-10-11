"""Inventory current compiler profiles without certifying retail object provenance.

Optional annotations live in config/us/compiler_profile_evidence.json::profiles.
Each slot may list byte_verified_evidence separately from
original_object_provenance: {status: unreviewed|reviewed, evidence: [...]}.
A reviewed assertion requires a nonempty evidence list. No build comment or
byte comparison automatically upgrades provenance.
"""
from project_layout import source_dir
import argparse
from collections import Counter
import json
from pathlib import Path

import build_dra
import source_inventory


ROOT = source_inventory.ROOT
EVIDENCE = "config/us/compiler_profile_evidence.json"
OUTPUT = "config/us/compiler_profiles.json"
UNCONSTRAINED = {"ordinary_c", "empty_c", "cxx_alias"}


def _compiler_name(path):
    value = str(path).replace("\\", "/").lower()
    if value.endswith("cc1plpsx.exe"):
        return "psyq46_cxx_2.95.2"
    if "/esa4.5/" in value:
        return "esa_psyq45"
    if "/psyq46/" in value:
        return "psyq46"
    if "gcc-2.8.1-psx" in value or value.endswith("/gcc-psx/cc1psx.exe"):
        return "shipped_gcc_2.8.1"
    if "gcc-2.7.2" in value:
        return "gcc_2.7.2"
    return "other_or_environment_override"


def _display_path(path, root):
    value = Path(path)
    try:
        return value.resolve().relative_to(root.resolve()).as_posix()
    except ValueError:
        return str(path).replace("\\", "/")


def load_evidence(root=ROOT):
    path = root / EVIDENCE
    if not path.exists():
        return {}
    data = json.loads(path.read_text(encoding="utf-8"))
    profiles = data.get("profiles")
    if not isinstance(profiles, dict):
        raise ValueError(f"{EVIDENCE}: expected a profiles object")
    for slot, annotation in profiles.items():
        if not isinstance(annotation, dict):
            raise ValueError(f"{EVIDENCE}: {slot} must be an object")
        byte = annotation.get("byte_verified_evidence", [])
        if not isinstance(byte, list) or not all(isinstance(x, str) and x for x in byte):
            raise ValueError(f"{EVIDENCE}: {slot} byte_verified_evidence must be a list of references")
        provenance = annotation.get("original_object_provenance", {})
        if not isinstance(provenance, dict):
            raise ValueError(f"{EVIDENCE}: {slot} original_object_provenance must be an object")
        status = provenance.get("status", "unreviewed")
        refs = provenance.get("evidence", [])
        if status not in ("unreviewed", "reviewed") or not isinstance(refs, list) or not all(isinstance(x, str) and x for x in refs):
            raise ValueError(f"{EVIDENCE}: {slot} invalid provenance status or evidence")
        if status == "reviewed" and not refs:
            raise ValueError(f"{EVIDENCE}: {slot} reviewed provenance requires evidence")
    return profiles


def build_report(units=None, root=None, evidence=None):
    """Describe manifest func rows mapped to source slots; never run a build."""
    units = source_inventory.UNITS if units is None else units
    root = ROOT if root is None else root
    evidence = load_evidence(root) if evidence is None else evidence
    excluded = source_inventory.sdk_symbols()
    slots = []
    unassigned = []
    total = Counter()
    for unit in units:
        definitions, stubs, duplicates = source_inventory.source_functions(unit)
        if duplicates:
            raise ValueError(f"{unit}: duplicate source definitions: {', '.join(duplicates)}")
        grouped = {}
        for row in source_inventory.manifest(unit):
            if row["kind"] != "func" or (unit, row["name"]) in excluded:
                continue
            name = row["name"]
            entry = definitions.get(name)
            source = entry["source"] if entry else stubs.get(name)
            if source is None:
                unassigned.append(dict(unit=unit, function=name, address=hex(row["address"])))
                continue
            if not source.startswith(source_dir(unit) + "/") or not source.endswith(".c"):
                raise ValueError(f"{unit}:{name}: unexpected source path {source}")
            category = entry["category"] if entry else "assembly"
            grouped.setdefault(source, []).append((row, category))
        for source, functions in sorted(grouped.items()):
            name = Path(source).name
            key = f"{unit}/{name}"
            compiler, flags, maspsx, asflags = build_dra.unit_toolchain(unit, name)
            base_compiler, _, _, _ = build_dra.unit_toolchain(unit)
            annotations = evidence.get(key, {})
            provenance = annotations.get("original_object_provenance", {})
            status = provenance.get("status", "unreviewed")
            refs = provenance.get("evidence", [])
            if status == "reviewed" and not refs:
                raise ValueError(f"{key}: reviewed provenance requires evidence")
            if status not in ("unreviewed", "reviewed"):
                raise ValueError(f"{key}: invalid provenance status {status}")
            if not isinstance(refs, list) or not all(isinstance(x, str) and x for x in refs):
                raise ValueError(f"{key}: provenance evidence must be a list of references")
            byte_evidence = annotations.get("byte_verified_evidence", [])
            if not isinstance(byte_evidence, list) or not all(isinstance(x, str) and x for x in byte_evidence):
                raise ValueError(f"{key}: byte_verified_evidence must be a list of references")
            categories = Counter(category for _, category in functions)
            total.update(categories)
            addresses = [row["address"] for row, _ in functions]
            compiler_isolation = len(functions) == 1 and str(compiler) != str(base_compiler)
            slots.append(dict(
                unit=unit, source_slot=source, profile_key=key,
                current_profile=dict(compiler=_display_path(compiler, root),
                                     compiler_family=_compiler_name(compiler),
                                     language="cxx" if build_dra.UNIT_CXX.get(key) else "c",
                                     cc1_flags=list(flags), maspsx_flags=list(maspsx), as_flags=list(asflags)),
                function_count=len(functions),
                unconstrained_count=sum(categories[c] for c in UNCONSTRAINED),
                categories=dict(categories),
                min_manifest_address=hex(min(addresses)),
                max_manifest_address=hex(max(addresses)),
                original_object_provenance=dict(status=status, evidence=refs),
                byte_verified_evidence=byte_evidence,
                review_flags=["needs_object_boundary_review"] if compiler_isolation else [],
            ))
    unknown_annotations = sorted(set(evidence) - {slot["profile_key"] for slot in slots})
    if unknown_annotations:
        raise ValueError("Evidence annotations without game-function slots: " + ", ".join(unknown_annotations))
    return dict(
        schema_version=1,
        scope="non-SDK manifest func rows mapped to current source slots",
        provenance_rule="byte matches do not establish original object/compiler settings",
        original_tu_boundary="unreviewed by default; source slots may be sector-derived",
        byte_verification_rule="references are explicit annotations only; this command does not build or verify",
        source_slots=slots,
        summary=dict(slot_count=len(slots), function_count=sum(slot["function_count"] for slot in slots),
                     unconstrained_count=sum(slot["unconstrained_count"] for slot in slots),
                     categories=dict(total), unassigned_function_count=len(unassigned),
                     single_function_compiler_isolations=sum(bool(slot["review_flags"]) for slot in slots),
                     reviewed_original_object_profiles=sum(slot["original_object_provenance"]["status"] == "reviewed" for slot in slots)),
        unassigned_manifest_functions=unassigned,
    )


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--save", action="store_true", help=f"write {OUTPUT}")
    parser.add_argument("--summary", action="store_true", help="print only bounded counts")
    args = parser.parse_args(argv)
    report = build_report()
    if args.save:
        (ROOT / OUTPUT).write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    if args.summary or args.save:
        s = report["summary"]
        print(f"Profiles: {s['slot_count']} slots, {s['function_count']} game functions, "
              f"{s['unconstrained_count']} unconstrained; "
              f"{s['unassigned_function_count']} unassigned, "
              f"{s['single_function_compiler_isolations']} single-function compiler isolations, "
              f"{s['reviewed_original_object_profiles']} provenance-reviewed")
    else:
        print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
