"""Generate remaining game-code candidates and preserve recorded failed attempts."""
import json
import re

from source_inventory import ROOT, UNITS, manifest, sdk_symbols, source_functions, mask


def build_worklist():
    excluded = sdk_symbols()
    candidates = []
    for unit in UNITS:
        definitions, stubs, _ = source_functions(unit)
        files = {p.stem: p for p in (ROOT / "asm/us" / unit).rglob("*.s")}
        calls, contents = {}, {}
        for name, path in files.items():
            text = mask(path.read_text(), strings=False)
            contents[name] = text
            for target in re.findall(r"\bjal\s+(func_[0-9a-fA-F]{8})", text):
                calls.setdefault(target, set()).add(name)
        attempts = {}
        for ledger in sorted((ROOT / "analysis/us" / unit).glob("*attempts.json")):
            entries = json.loads(ledger.read_text())
            if isinstance(entries, dict):
                if "attempts" in entries:
                    entries = entries["attempts"]
                else:
                    normalized = []
                    for key, entry in entries.items():
                        address = re.search(r"_([0-9a-fA-F]{5,8})$", key)
                        if key.startswith("unresolved_") and isinstance(entry, dict) and address:
                            normalized.append(dict(entry, function=f"func_{(int(address[1], 16) | 0x80000000):08X}",
                                                   outcome="unmatched", reason=entry.get("status", "unresolved attempt")))
                    entries = normalized
            for entry in entries:
                name = entry.get("function", entry.get("name"))
                if name:
                    attempts.setdefault(name, []).append(entry)
        for row in manifest(unit):
            name = row["name"]
            if (unit, name) in excluded or row["kind"] not in ("func", "asm", "data"):
                continue
            entry = definitions.get(name)
            if row["kind"] == "func" and entry and entry["category"] not in ("assisted_c", "source_hack_c"):
                continue
            path = files.get(name)
            text = contents.get(name, "")
            declared = re.search(r"nonmatching\s+\w+,\s*(0x[0-9a-fA-F]+|\d+)", text)
            instruction_addresses = [int(a, 16) for a in re.findall(r"/\*\s*[0-9a-fA-F]+\s+([0-9a-fA-F]{8})", path.read_text() if path else "")]
            size = int(declared[1], 0) if declared else max(instruction_addresses) - min(instruction_addresses) + 4 if instruction_addresses else None
            indirect = bool(re.search(r"\bjalr\b", text))
            gte = bool(re.search(r"\b(?:mfc2|mtc2|cfc2|ctc2|lwc2|swc2|gte_\w+)\b", text, re.I))
            history = attempts.get(name, [])
            difficulty = "review" if row["kind"] != "func" else "complex_assisted_source" if entry else "review" if size is None else "complex" if indirect or gte or size > 256 else "straightforward_candidate"
            if row["kind"] == "func" and history and any(e.get("outcome") not in ("matched", "verified", "accepted") for e in history):
                difficulty = "complex_after_failed_attempt"
            candidates.append(dict(unit=unit, function=name, address=hex(row["address"]), manifest_kind=row["kind"],
                                   source_slot=entry["source"] if entry else stubs.get(name), assembly=path.relative_to(ROOT).as_posix() if path else None,
                                   work_type="review_non_function_boundary" if row["kind"] != "func" else "review_assembly_constraints" if entry else "recover_game_source",
                                   bytes=size, indirect_calls=indirect, gte=gte,
                                   direct_callers_in_unit=sorted(calls.get(name, [])), difficulty=difficulty, attempts=history,
                                   suggested_model="gpt-6.1-sol medium"))
    candidates.sort(key=lambda c: (c["difficulty"] != "straightforward_candidate", c["bytes"] if c["bytes"] is not None else 1 << 30, c["unit"], c["address"]))
    result = dict(candidates=candidates, candidate_count=len(candidates),
                  notes=["size/control-flow complexity is a scheduling hint, not proof of easy matching",
                         "all decompilation subagents use GPT-6.1 Sol medium per the user's current preference",
                         "all non-func game assembly entries remain in inventory review",
                         "callers are qualified by unit; cross-overlay interfaces require separate resolution",
                         "SDK exclusions are never scheduled for C conversion"])
    return result


def main():
    result = build_worklist()
    (ROOT / "config/us/worklist.json").write_text(json.dumps(result, indent=2) + "\n")
    print(f"Remaining game source and boundary-review candidates: {result['candidate_count']}")


if __name__ == "__main__":
    main()
