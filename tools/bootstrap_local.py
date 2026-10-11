"""Restore hash-identified local build inputs from the accepted original workspace.

Does not distribute game files or overwrite accepted source. Splat alone cannot
recreate the reviewed manual ownership/boundary changes in this imported split.
"""
import argparse,hashlib,json,shutil
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--from',dest='original',type=Path)
    parser.add_argument('--check',action='store_true')
    args=parser.parse_args()
    rows=json.loads((ROOT/'docs/import_manifest.json').read_text())['local_inputs']
    if args.original:
        source=args.original.resolve()
        # Validate all inputs before writing any destination; no executable launch.
        for row in rows:
            p=source/row['original']
            if not p.is_file() or sha(p)!=row['original_sha256']:parser.error('Missing/changed original input: '+row['original'])
        mappings=json.loads((ROOT/'docs/import_manifest.json').read_text())['layout_mapping']
        for row in rows:
            p=source/row['original'];q=ROOT/row['destination']
            if q.exists():
                if sha(q)!=row['export_sha256']:parser.error('Refusing to overwrite changed input: '+row['destination'])
                continue
            raw=p.read_bytes()
            if p.suffix in ['.s','.inc','.h','.c'] and row['original'].startswith(('asm/USA/','assets/')):
                text=raw.decode('utf-8')
                for old,new in mappings.items():text=text.replace(old+'/',new+'/') if old.startswith('src/') else text.replace(old,new)
                raw=text.replace('"asm", "USA"','"asm", "us"').encode('utf-8')
                raw=raw.replace(b'\r\n',b'\n')
            if hashlib.sha256(raw).hexdigest()!=row['export_sha256']:parser.error('Migration hash mismatch: '+row['destination'])
            q.parent.mkdir(parents=True,exist_ok=True);q.write_bytes(raw)
    missing=[row['destination'] for row in rows if not (ROOT/row['destination']).is_file()]
    if missing:parser.error('Local inputs missing; use --from with the original workspace. First missing: '+missing[0])
    print(f'Local build inputs present: {len(rows)}. Full byte/placement verification is tools/verify.py.')
if __name__=='__main__':main()
