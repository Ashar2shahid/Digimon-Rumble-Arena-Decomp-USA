"""Generate the reviewed assembly split from verified USA retail binaries.

Recipes contain section/label/alignment scaffolding, byte ranges and symbolic
operand bindings. Instruction words and literal game data are read from the
user's binaries, never from cached assembly or compiler-produced output.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import tempfile

import build_dra

ROOT = Path(__file__).resolve().parents[1]
SCHEMA = 1


def configure_decoder():
    try:
        import rabbitizer
        from importlib.metadata import version
        if version('rabbitizer') != '1.16.2':
            raise ValueError('Rabbitizer 1.16.2 is required; install requirements.txt')
    except ImportError as error:
        raise ValueError('Install Python dependencies: python -m pip install -r requirements.txt') from error
    rabbitizer.config.pseudos_pseudoMove = False
    rabbitizer.config.regNames_vr4300Cop0NamedRegisters = False
    rabbitizer.config.toolchainTweaks_gnuMode = True
    return rabbitizer


def checked_range(data, cfg, address, size):
    address = int(address, 16) if isinstance(address, str) else address
    offset = address - cfg['vram'] + cfg['file_base']
    if offset < cfg['file_base'] or size < 0 or offset + size > len(data):
        raise ValueError(f'Recipe range outside retail image: {address:#x}, {size}')
    return offset, data[offset:offset + size]


def render_file(records, data, cfg, rabbitizer):
    lines = []
    for row in records:
        if isinstance(row, str):
            lines.append(row)
            continue
        kind, address = row[:2]
        if kind == 'i':
            offset, raw = checked_range(data, cfg, address, 4)
            instruction = rabbitizer.Instruction(int.from_bytes(raw, 'little'), int(address, 16),
                                                rabbitizer.InstrCategory.R3000GTE)
            text = instruction.disassemble(immOverride=row[2]) if len(row) > 2 else instruction.disassemble()
            lines.append(f'    /* {offset:X} {address} {raw.hex().upper()} */  {text}')
        elif kind == 'd':
            width = row[2]
            offset, raw = checked_range(data, cfg, address, width)
            directive = {1: '.byte', 2: '.short', 4: '.word'}[width]
            lines.append(f'    /* {offset:X} {address} */ {directive} 0x{int.from_bytes(raw, "little"):0{width * 2}X}')
        elif kind == 'p':
            offset, raw = checked_range(data, cfg, address, 4)
            lines.append(f'    /* {offset:X} {address} */ .word {row[2]}')
        elif kind == 'bytes':
            offset, raw = checked_range(data, cfg, address, row[2])
            for start in range(0, len(raw), 16):
                chunk = ', '.join(f'0x{x:02X}' for x in raw[start:start + 16])
                lines.append(f'    .byte {chunk}')
        else:
            raise ValueError('Unknown split recipe operation: ' + str(kind))
    return '\n'.join(lines) + '\n'


def safe_path(root, relative):
    path = (root / relative).resolve()
    if not path.is_relative_to(root.resolve()) or path == root.resolve():
        raise ValueError('Unsafe split destination: ' + relative)
    return path


def generate(root=ROOT, check=False):
    root = root.resolve()
    rabbitizer = configure_decoder()
    outputs = {}
    recipe_hashes = {}
    for unit in build_dra.UNITS:
        cfg = build_dra.CONFIG[unit]
        target = root / cfg['target']
        if not target.is_file():
            raise ValueError('Missing game input; run tools/setup_game.py first: ' + cfg['target'])
        data = target.read_bytes()
        if hashlib.sha1(data).hexdigest() != cfg['sha1']:
            raise ValueError('Unsupported or changed retail target: ' + cfg['target'])
        recipe_path = root / 'config/us/split' / (unit + '.json')
        raw_recipe = recipe_path.read_bytes()
        recipe_hashes[unit] = hashlib.sha256(raw_recipe).hexdigest()
        recipe = json.loads(raw_recipe)
        if recipe['schema'] != SCHEMA or recipe['unit'] != unit or recipe['target_sha1'] != cfg['sha1']:
            raise ValueError('Recipe identity differs from the supported retail target: ' + unit)
        for name, row in recipe['files'].items():
            path = f'asm/us/{unit}/{name}'
            if unit == 'main' and name == 'header.s':
                text = '.section .data\n.balign 4\n.incbin "disks/us/SLUS_014.04", 0, 2048\n'
            else:
                text = render_file(row['records'], data, cfg, rabbitizer)
            raw = text.encode('utf-8')
            if hashlib.sha256(raw).hexdigest() != row['generated_sha256']:
                raise ValueError('Disassembler output differs from the reviewed recipe: ' + path)
            if path in outputs:
                raise ValueError('Duplicate split output: ' + path)
            outputs[path] = (raw, row['legacy_sha256'])
        for asset in recipe.get('assets', []):
            offset, raw = checked_range(data, cfg, asset['address'], asset['size'])
            if hashlib.sha256(raw).hexdigest() != asset['sha256']:
                raise ValueError('Asset range hash differs: ' + asset['path'])
            outputs[asset['path']] = (raw, asset['sha256'])
    # Refuse unknown assembly: standalone files would otherwise be linked too.
    for path in (root / 'asm/us').rglob('*.s'):
        if path.relative_to(root).as_posix() not in outputs:
            raise ValueError('Unmanaged assembly file; preserve and review it: ' + str(path))
    for relative, (raw, legacy) in outputs.items():
        path = safe_path(root, relative)
        if path.exists():
            actual = hashlib.sha256(path.read_bytes()).hexdigest()
            expected = hashlib.sha256(raw).hexdigest()
            if actual != expected and (check or actual != legacy):
                raise ValueError('Changed split output; refusing to overwrite: ' + relative)
        elif check:
            raise ValueError('Missing generated input: ' + relative)
    if not check:
        for relative, (raw, legacy) in outputs.items():
            path = safe_path(root, relative)
            if path.exists() and path.read_bytes() == raw:
                continue
            path.parent.mkdir(parents=True, exist_ok=True)
            with tempfile.NamedTemporaryFile(dir=path.parent, delete=False) as temporary:
                temporary.write(raw)
                staging = Path(temporary.name)
            staging.replace(path)
        record = dict(schema=SCHEMA, targets={u: build_dra.CONFIG[u]['sha1'] for u in build_dra.UNITS},
                      recipe_sha256=recipe_hashes,
                      outputs={p: hashlib.sha256(raw).hexdigest() for p, (raw, _) in outputs.items()})
        output = root / 'build/us/generated-inputs.json'
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    print(f'{"Checked" if check else "Generated"} {len(outputs)} reviewed assembly/asset inputs from 14 verified USA binaries.')
    return len(outputs)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true', help='verify the generated split without writing')
    args = parser.parse_args()
    try:
        generate(check=args.check)
    except (OSError, ValueError, KeyError) as error:
        parser.exit(1, f'Split generation failed: {error}\n')


if __name__ == '__main__':
    main()
