"""Compile C with old GCC; Linux staging avoids old stat() limits on DrvFS."""
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def compile_c(source: Path, output: Path, version="2.8.1", aspsx="2.79"):
    source = source.resolve()
    output = output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    compiler = ROOT / ".tools" / f"gcc-{version}"
    with tempfile.TemporaryDirectory(prefix="dra-compile-") as temp:
        work = Path(temp)
        shutil.copytree(ROOT / "include", work / "include")
        shutil.copyfile(source, work / source.name)
        sections = ["-ffunction-sections"] if version == "2.8.1" else []
        subprocess.run([str(compiler / "gcc"), f"-B{compiler}/", "-O2", "-G0",
                        "-msoft-float", "-fno-builtin", *sections,
                        "-Iinclude", "-S", source.name, "-o", str(output)],
                       cwd=work, check=True)
    text = output.read_text()
    if version == "2.7.2":
        text = re.sub(r"(?m)^(\s*\.globl\s+(func_[0-9A-F]{8}))$",
                      lambda m: f'.section .{m[2]},"ax",@progbits\n.align 2\n{m[1]}', text)
    converted = subprocess.run([sys.executable, str(ROOT / ".external/maspsx/maspsx.py"),
                                f"--aspsx-version={aspsx}"], input=text,
                               capture_output=True, text=True, check=True)
    gnu = output.with_suffix(".gnu.s")
    gnu.write_text(converted.stdout)
    obj = output.with_suffix(".o")
    subprocess.run(["mipsel-linux-gnu-as", "-EL", "-mips1", "-G0", "-o", str(obj), str(gnu)],
                   check=True)
    return obj


if __name__ == "__main__":
    compile_c(Path(sys.argv[1]), Path(sys.argv[2]), *sys.argv[3:])
