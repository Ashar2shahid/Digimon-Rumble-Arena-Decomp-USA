"""Generate address-preserving PS1 assembly and function inventories."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--drafts", action="store_true", help="also generate unverified m2c C drafts")
    args = parser.parse_args()
    config = json.loads(Path("config/us/project.json").read_text())
    for module in config["modules"]:
        path = Path(module["path"])
        if hashlib.sha1(path.read_bytes()).hexdigest() != module["sha1"]:
            raise ValueError(f"Wrong input revision: {path}")
        start, end, base = (int(module[key], 0) for key in ("text_start", "text_end", "file_base"))
        output = Path("analysis/us") / module["name"]
        output.mkdir(parents=True, exist_ok=True)
        assembly = Path("asm/us") / module["name"]
        assembly.mkdir(parents=True, exist_ok=True)
        cmd = [sys.executable, "-m", "spimdisasm", "singleFileDisasm", str(path), str(output),
               "--start", f"{start:X}", "--end", f"{end:X}", "--vram", f"{base + start:X}",
               "--gp", module["gp"], "--endian", "little", "--arch-level", "MIPS1",
               "--instr-category", "r3000gte", "--compiler", "PSYQ", "--split-functions", str(assembly),
               "--function-info", str(output / "functions.csv"), "--save-context", str(output / "context.csv"),
               "--no-asm-prelude-use-includes", "--no-cop0-named-registers",
               "--no-libultra-syms", "--no-hardware-regs", "--quiet"]
        subprocess.run(cmd, check=True)
        count = len(list(assembly.glob("*.s")))
        print(f"{module['name']}: {count} provisional function splits", flush=True)
        if args.drafts:
            full_asm = next(output.glob("*.text.s"))
            with (output / "drafts.c").open("w") as dest, (output / "m2c.log").open("w") as log:
                result = subprocess.run([sys.executable, ".tools/m2c/m2c.py", "-t", "mipsel-gcc-c",
                                         str(full_asm)], stdout=dest, stderr=log)
            print(f"  m2c exit {result.returncode}; drafts need manual types and verification", flush=True)


if __name__ == "__main__":
    main()
