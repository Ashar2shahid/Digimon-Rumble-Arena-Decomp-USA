"""Classify source representations without treating INCLUDE_ASM as recovered C."""
from project_layout import source_dir
import json
import re
from pathlib import Path

ROOT = Path(__file__).absolute().parent.parent
UNITS = ["main", "game", "title", "movie"] + [f"st{i:02d}" for i in range(10)]
TOKEN = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')
HEAD = re.compile(r"(?m)^[^\n;={}]*?\b(func_[0-9A-Fa-f]{8})\s*\([^;{}()]*\)\s*")
STUB = re.compile(r'INCLUDE_ASM\("[^"]+",\s*(func_[0-9A-Fa-f]{8})\)')
ALIAS = re.compile(r"\.set\s+(func_[0-9A-Fa-f]{8})\s*,\s*([\w.$]+)")


def mask(text, strings=True):
    def replace(match):
        value = match.group()
        if not strings and value[0] in "\"'":
            return value
        return "".join("\n" if c == "\n" else " " for c in value)
    return TOKEN.sub(replace, text)


def manifest(unit):
    rows = []
    for line in (ROOT / "config/us/functions" / f"{unit}.txt").read_text().splitlines():
        fields = line.split()
        if len(fields) >= 3 and not line.lstrip().startswith("#"):
            rows.append(dict(name=fields[0], address=int(fields[1], 16), kind=fields[2]))
    overrides = ROOT / "config/us/boundary_overrides.json"
    if overrides.exists():
        by_name = {row["name"]: row for row in rows}
        for entry in json.loads(overrides.read_text())["overrides"]:
            if entry["unit"] != unit:
                continue
            row = by_name.get(entry["symbol"])
            if row is None or row["address"] != int(entry["address"], 16) or row["kind"] != entry["kind"]:
                raise ValueError(f"Reviewed boundary correction was lost: {unit}:{entry['symbol']}")
    return rows


def source_functions(unit):
    """Bodies are lexical estimates; linked-map/full-binary gates provide evidence."""
    definitions, stubs, duplicates = {}, {}, []
    for path in sorted((ROOT / source_dir(unit)).rglob("*.c")):
        if unit == "game" and "stages" in path.relative_to(ROOT).parts:
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        clean = mask(text)
        commentless = mask(text, strings=False)
        relative = path.relative_to(ROOT).as_posix()
        for match in STUB.finditer(commentless):
            stubs[match[1]] = relative
        for match in HEAD.finditer(clean):
            pos = match.end()
            knr = False
            if pos < len(clean) and clean[pos] == ";":
                continue
            if pos >= len(clean) or clean[pos] != "{":
                # The one legacy K&R definition has declarations between ) and {.
                end = clean.find("{", pos, pos + 1000)
                declarations = clean[pos:end] if end != -1 else ""
                if not declarations.strip() or not re.fullmatch(r"[\w\s*,;\[\]]+", declarations) or ";" not in declarations:
                    continue
                pos, knr = end, True
            depth, end = 1, pos + 1
            while end < len(clean) and depth:
                depth += (clean[end] == "{") - (clean[end] == "}")
                end += 1
            if depth:
                raise ValueError(f"Unclosed function body: {relative}:{match[1]}")
            body = clean[pos + 1:end - 1]
            constrained = bool(re.search(r"\b(?:__asm__|__asm|asm)\b", body))
            documented_hack = bool(re.search(r"register.forcing|dead initiali[sz]ers|read before (?:its )?assignment|uninitiali[sz]ed.*(?:steer|forc)|steers? cc1", text[match.start():end], re.I))
            category = "assisted_c" if constrained else "source_hack_c" if documented_hack else "empty_c" if not body.strip() else "ordinary_c"
            entry = dict(source=relative, line=text.count("\n", 0, match.start()) + 1,
                         category=category, knr=knr)
            if match[1] in definitions:
                duplicates.append(match[1])
            definitions[match[1]] = entry
        for match in ALIAS.finditer(commentless):
            if match[1] in definitions:
                if definitions[match[1]]["source"] == relative:
                    definitions[match[1]]["mangled_name"] = match[2]
                    continue
                duplicates.append(match[1])
            definitions[match[1]] = dict(source=relative, line=text.count("\n", 0, match.start()) + 1,
                                         category="cxx_alias", mangled_name=match[2], knr=False)
    return definitions, stubs, duplicates


def sdk_symbols():
    path = ROOT / "config/us/psyq_funcs.txt"
    excluded = set()
    if path.exists():
        for line in path.read_text().splitlines():
            fields = line.split()
            if fields and not line.lstrip().startswith("#"):
                excluded.add((fields[0], fields[1]))
    return excluded
