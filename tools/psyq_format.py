"""Minimal PSY-Q LIB/OBJ parser (format per ttkb-oss/psy-k src/lib.rs)."""
import struct, sys, os

def u16(b,o): return struct.unpack_from('<H',b,o)[0],o+2
def u32(b,o): return struct.unpack_from('<I',b,o)[0],o+4
def u8(b,o): return b[o],o+1

def expr_size(b,o):
    t=b[o]
    if t==0x00: return 1+4
    if t in (0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,0x12,0x14,0x16): return 1+2
    if 0x20<=t<=0x4A and t%2==0:
        p=o+1
        s1=expr_size(b,p); p+=s1
        s2=expr_size(b,p)
        return 1+s1+s2
    raise ValueError('expr tag %02x at %x'%(t,o))

def parse_sections(b, base):
    """b=obj bytes, base=obj offset within file (for reporting). Returns (sections list, text_bytes, names, end_off)."""
    o=0
    assert b[o:o+3]==b'LNK', b[o:o+3]
    ver=b[o+3]; o+=4
    sections=[]
    while True:
        tag=b[o]; o+=1
        if tag==0x00:
            sections.append(('NOP',None)); break
        elif tag==0x02:
            sz,o=u16(b,o); code=b[o:o+sz]; o+=sz
            sections.append(('Code',code))
        elif tag==0x04:
            o+=4; sections.append(('RunAtOffset',None))
        elif tag==0x06:
            sid,o=u16(b,o); sections.append(('SectionSwitch',sid))
        elif tag==0x08:
            sz,o=u32(b,o); sections.append(('BSS',sz))
        elif tag==0x0A:
            pt=b[o]; po,_=u16(b,o+1); es=expr_size(b,o+3); o+=3+es
            sections.append(('Patch',(pt,po)))
        elif tag==0x0C:
            num,o=u16(b,o); sec,o=u16(b,o); off,o=u32(b,o); ln,o=u8(b,o)
            nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('XDEF',(sec,off,nm)))
        elif tag==0x0E:
            num,o=u16(b,o); ln,o=u8(b,o); nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('XREF',nm))
        elif tag==0x10:
            sec,o=u16(b,o); grp,o=u16(b,o); al,o=u8(b,o); ln,o=u8(b,o)
            nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('LNKHeader',(sec,grp,nm)))
        elif tag==0x12:
            sec,o=u16(b,o); off,o=u32(b,o); ln,o=u8(b,o); nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('LocalSymbol',(sec,off,nm)))
        elif tag==0x14:
            o+=2; o+=1; ln,o=u8(b,o); o+=ln; sections.append(('GroupSymbol',None))
        elif tag in (0x16,0x18,0x1A):
            o+=2; sections.append(('Reg',None))
        elif tag==0x1C:
            num,o=u16(b,o); ln,o=u8(b,o); nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('Filename',nm))
        elif tag==0x1E: o+=6; sections.append(('SetToFile',None))
        elif tag==0x20: o+=4; sections.append(('SetToLine',None))
        elif tag==0x22: sections.append(('IncLine',None))
        elif tag==0x24: o+=1; sections.append(('IncLineB',None))
        elif tag==0x26: o+=4; sections.append(('IncLineW',None))
        elif tag==0x28:
            sec,o=u16(b,o); off,o=u32(b,o); ln,o=u8(b,o); nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('LocalSymbol',(sec,off,nm)))
        elif tag==0x2A: o+=2; sections.append(('Reg',None))
        elif tag==0x2C: o+=3; sections.append(('SetMXInfo',None))
        elif tag==0x2E: o+=1; sections.append(('CPU',None))
        elif tag==0x30:
            o+=2; o+=2; o+=4; ln,o=u8(b,o); o+=ln; sections.append(('XBSS',None))
        elif tag==0x32: o+=2; sections.append(('SLD',None))
        elif tag==0x34: o+=3; sections.append(('SLD',None))
        elif tag==0x36: o+=6; sections.append(('SLD',None))
        elif tag==0x38: o+=6; sections.append(('SLD',None))
        elif tag==0x3A: o+=8; sections.append(('SLD',None))
        elif tag==0x3C: o+=2; sections.append(('EndSLD',None))
        elif tag in (0x3E,0x40,0x42,0x48): o+=4; sections.append(('Repeat',None))
        elif tag==0x44: o+=3; sections.append(('ProcCall',None))
        elif tag==0x46: o+=2; sections.append(('ProcDef',None))
        elif tag==0x4A:
            sec,o=u16(b,o); off,o=u32(b,o); fil,o=u16(b,o); lin,o=u32(b,o)
            fr,o=u16(b,o); fs,o=u32(b,o); rp,o=u16(b,o); mk,o=u32(b,o); mo,o=u32(b,o)
            ln,o=u8(b,o); nm=b[o:o+ln].decode('latin1'); o+=ln
            sections.append(('FunctionStart',(sec,off,nm)))
        elif tag in (0x4C,0x4E,0x50): o+=10; sections.append(('FuncEnd',None))
        elif tag==0x52:
            sec,o=u16(b,o); val,o=u32(b,o); cls,o=u16(b,o); dt,o=u16(b,o); sz,o=u32(b,o)
            ln,o=u8(b,o); o+=ln; sections.append(('Def',None))
        elif tag==0x54:
            sec,o=u16(b,o); val,o=u32(b,o); cls,o=u16(b,o); dt,o=u16(b,o); sz,o=u32(b,o)
            dm,o=u16(b,o)
            if dm==1: o+=4
            ts,o=u8(b,o); o+=ts; ns,o=u8(b,o); o+=ns
            sections.append(('Def2',None))
        else:
            raise ValueError('section tag %02x at %x'%(tag,o-1))
    return sections, ver, o

def parse_lib(path):
    b=open(path,'rb').read()
    assert b[0:3]==b'LIB'
    ver=b[3]
    o=4
    mods=[]
    while o < len(b):
        name=b[o:o+8].decode('latin1').rstrip(' \x00')
        created,_=u32(b,o+8)
        offset,_=u32(b,o+12)
        size,_=u32(b,o+16)
        p=o+20
        exports=[]
        while True:
            ln=b[p]; p+=1
            if ln==0: break
            exports.append(b[p:p+ln].decode('latin1')); p+=ln
        obj_start=o+offset
        obj_end=o+size
        mods.append((name,exports,obj_start,obj_end))
        o=o+size
    return ver,mods

if __name__=='__main__':
    p=sys.argv[1]
    ver,mods=parse_lib(p)
    print('version',ver,'modules',len(mods))
    for name,exports,os_,oe in mods[:5]:
        print(name,exports,hex(os_),hex(oe))
