"""Save verified build inputs without overwriting an earlier checkpoint."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import shutil

from source_inventory import ROOT, UNITS
from verify import current_verification, digest


def main():
    states = [current_verification(unit) for unit in UNITS]
    if not all(state['current_verified_build'] for state in states):
        raise ValueError('Stop source writers and run the complete verification gate first')
    progress = json.loads((ROOT / 'config/us/progress.json').read_text())
    if not progress['all_modules_verified'] or progress['inventory_problems']:
        raise ValueError('Refresh the verified progress snapshot first')
    records = {unit: json.loads((ROOT / f'build/us/verification/{unit}.json').read_text())
               for unit in UNITS}
    inputs = {}
    for record in records.values():
        for name, expected in record['inputs'].items():
            if name in inputs and inputs[name] != expected:
                raise ValueError(f'Units recorded inconsistent inputs: {name}')
            inputs[name] = expected
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ')
    checkpoint = ROOT / 'analysis/checkpoints' / stamp
    checkpoint.mkdir(parents=True, exist_ok=False)
    for name, expected in sorted(inputs.items()):
        destination = checkpoint / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / name, destination)
        if digest(destination) != expected or digest(ROOT / name) != expected:
            raise ValueError(f'Input changed during snapshot: {name}')
    shutil.copytree(ROOT / 'build/us/verification', checkpoint / 'verification')
    for name in ('progress.json', 'worklist.json', 'sdk_references.json'):
        shutil.copy2(ROOT / 'config/us' / name, checkpoint / name)
    for source in (ROOT / 'tools').glob('*.py'):
        destination = checkpoint / 'tools' / source.name
        if not destination.exists():
            shutil.copy2(source, destination)
    shutil.copy2(ROOT / 'decomp.ps1', checkpoint / 'decomp.ps1')
    metadata = dict(created_at=datetime.now(timezone.utc).isoformat(),
                    verification='14 complete byte comparisons and manifest/source-object placement checks',
                    recorded_inputs=len(inputs), copied_inputs_sha256=inputs,
                    main_verified_at=records['main']['verified_at'],
                    game_functions=progress['game_manifest_functions'],
                    unconstrained_source=progress['verified_unconstrained_source'])
    (checkpoint / 'checkpoint.json').write_text(json.dumps(metadata, indent=2) + '\n')
    print(checkpoint.relative_to(ROOT).as_posix())


if __name__ == '__main__':
    main()
