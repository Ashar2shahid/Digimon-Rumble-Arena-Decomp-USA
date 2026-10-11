"""Extract and validate the supported USA code targets from a PS1 disc image.

Accepts a 2048-byte ISO, raw 2352-byte BIN, or one-track CUE. No disc image is
modified. All fourteen target hashes are checked before installing any files.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import tempfile

from extract_disc import Disc
from extract_vfs import extract
import build_dra

ROOT = Path(__file__).resolve().parents[1]


def validated_targets(directory: Path) -> dict[str, dict]:
    results = {}
    for unit, cfg in build_dra.CONFIG.items():
        relative = 'SLUS_014.04' if unit == 'main' else 'bin/' + unit + '.bin'
        path = directory / relative
        if not path.is_file():
            raise ValueError('Missing USA code target: ' + relative)
        raw = path.read_bytes()
        actual = hashlib.sha1(raw).hexdigest()
        if actual != cfg['sha1']:
            raise ValueError(f'Unsupported game revision: {relative}: expected {cfg["sha1"]}, got {actual}')
        results[unit] = dict(path=cfg['target'], size=len(raw), sha1=actual,
                             sha256=hashlib.sha256(raw).hexdigest())
    return results


def setup(image: Path, root: Path = ROOT) -> dict:
    root = root.resolve()
    (root / 'build').mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='disc-setup-', dir=root / 'build') as temporary:
        stage = Path(temporary)
        disc = Disc(image)
        try:
            entries = disc.files()
            required = {}
            for name in ('SLUS_014.04', 'A.VFS'):
                found = [e for e in entries if e['path'].upper() == name]
                if len(found) != 1:
                    raise ValueError(f'Disc does not contain the supported USA file {name}')
                result = disc.extract(found[0], stage)
                if not result['extracted']:
                    raise ValueError(f'Expected a Form 1 file: {name}')
                original = stage / found[0]['path']
                canonical = stage / name
                if original != canonical:
                    original.rename(canonical)
                required[name] = result
            image_format = dict(sector_size=disc.sector_size, payload_offset=disc.payload_offset,
                                volume_id=disc.volume)
        finally:
            disc.stream.close()
        # Fail quickly on JP, PAL, or a changed executable before inflating overlays.
        actual = hashlib.sha1((stage / 'SLUS_014.04').read_bytes()).hexdigest()
        if actual != build_dra.CONFIG['main']['sha1']:
            raise ValueError('Unsupported executable: expected USA SLUS_014.04 SHA-1 ' +
                             build_dra.CONFIG['main']['sha1'] + ', got ' + actual)
        wanted = {'bin/' + unit + '.bin' for unit in build_dra.CONFIG if unit != 'main'}
        files = extract(stage / 'A.VFS', stage, only=wanted)
        results = validated_targets(stage)
        # Check all destinations before changing any accepted game inputs.
        for unit, row in results.items():
            destination = root / row['path']
            if destination.exists() and hashlib.sha256(destination.read_bytes()).hexdigest() != row['sha256']:
                raise ValueError('Refusing to overwrite changed game input: ' + row['path'])
        for unit, row in results.items():
            original = stage / ('SLUS_014.04' if unit == 'main' else 'bin/' + unit + '.bin')
            destination = root / row['path']
            destination.parent.mkdir(parents=True, exist_ok=True)
            if not destination.exists():
                shutil.copyfile(original, destination)
        record = dict(format=image_format, targets=results, archive_files=files)
        output = root / 'build/us/setup-game.json'
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(record, indent=2) + '\n', encoding='utf-8')
    return record


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('image', type=Path, help='USA ISO, BIN, or one-track CUE path')
    args = parser.parse_args()
    try:
        record = setup(args.image)
    except (OSError, ValueError) as error:
        parser.exit(1, f'Game setup failed: {error}\n')
    print('Extracted and verified USA executable and 13 inflated overlays (14/14).')
    for unit, target in record['targets'].items():
        print(f'{unit}: {target["path"]} ({target["size"]:,} bytes)')


if __name__ == '__main__':
    main()
