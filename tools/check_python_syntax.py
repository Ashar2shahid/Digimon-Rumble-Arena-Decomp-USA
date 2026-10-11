"""Parse project Python sources without requiring proprietary local dependencies."""
from pathlib import Path
import ast
ROOT=Path(__file__).resolve().parents[1]
paths=list((ROOT/'tools').rglob('*.py'))+list((ROOT/'tests').rglob('*.py'))
for p in paths:ast.parse(p.read_text(encoding='utf-8'),filename=str(p))
print(f'Python syntax checked: {len(paths)} files')
