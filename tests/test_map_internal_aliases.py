"""Relative aliases need reviewed metadata and an emitted parent."""
import json
from pathlib import Path
import sys,tempfile,unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
import build_dra

class InternalAliasTests(unittest.TestCase):
 def setUp(self):
  base=Path(build_dra.ROOT)/'analysis/test-temp';base.mkdir(parents=True,exist_ok=True)
  temp=tempfile.TemporaryDirectory(dir=base);self.addCleanup(temp.cleanup);self.root=Path(temp.name)
  self.patcher=patch.object(build_dra,'ROOT',str(self.root));self.patcher.start();self.addCleanup(self.patcher.stop)
  (self.root/'build/us').mkdir(parents=True);(self.root/'config/us').mkdir(parents=True)
  self.map=self.root/'build/us/main.map';self.metadata=self.root/'config/us/boundary_overrides.json'
  self.metadata.write_text(json.dumps(dict(overrides=[dict(unit='main',symbol='func_internal',kind='internal',parent='func_parent',offset=20)])))
 def write_map(self,address=0x80020014,parent=True,expression='(func_parent + 0x14)'):
  self.map.write_text(f'                0x{address:08x} func_internal = {expression}\n'+
   (' build/us/src/engine/slot.c.o(.text)\n                0x80020000 func_parent\n' if parent else ''))
 def test_reviewed_alias_follows_shifted_parent_and_owns_its_object(self):
  self.map.write_text('                0x80020114 func_internal = (func_parent + 0x14)\n build/us/src/engine/slot.c.o(.text)\n                0x80020100 func_parent\n')
  self.assertIn(('func_internal',0x80020114,'build/us/src/engine/slot.c.o'),build_dra.parse_map_symbols('main'))
 def test_wrong_value_or_missing_parent_cannot_establish_placement(self):
  for address,parent in [(0x80020018,True),(0x80020014,False)]:
   self.write_map(address,parent)
   self.assertFalse(any(n=='func_internal' for n,_,_ in build_dra.parse_map_symbols('main')))
 def test_unreviewed_offset_or_absolute_binding_is_rejected(self):
  for expression in ['(func_parent + 0x18)','0x80020014']:
   self.write_map(expression=expression)
   self.assertFalse(any(n=='func_internal' for n,_,_ in build_dra.parse_map_symbols('main')))
  self.metadata.unlink();self.write_map()
  self.assertFalse(any(n=='func_internal' for n,_,_ in build_dra.parse_map_symbols('main')))

if __name__=='__main__':unittest.main()
