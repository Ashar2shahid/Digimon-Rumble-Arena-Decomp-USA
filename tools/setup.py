"""Install pinned project tools into .venv-wsl and .tools. Run with WSL Python 3.12+."""
from pathlib import Path
import subprocess
import sys
import venv

REPOS = {
    "m2c": ("https://github.com/matt-kempster/m2c.git", "708d2d2cb2698f091a92492b328f73b24209f72d"),
    "maspsx": ("https://github.com/mkst/maspsx.git", "e85ecb373828aabea96d7e6400974d4f91ce8c74"),
}


def run(*command):
    subprocess.run(command, check=True)


def main():
    if sys.platform != "linux" or sys.version_info < (3, 12):
        raise SystemExit("Use Python 3.12 or newer inside WSL Ubuntu")
    for executable in ("git", "mipsel-linux-gnu-as", "mipsel-linux-gnu-ld", "mipsel-linux-gnu-objcopy", "mipsel-linux-gnu-nm"):
        run(executable, "--version")
    environment = Path(".venv-wsl")
    if not (environment / "bin/python").exists():
        venv.EnvBuilder(with_pip=True).create(environment)
    python = str(environment / "bin/python")
    run(python, "-m", "pip", "install", "-r", "requirements.txt")
    for name, (url, commit) in REPOS.items():
        directory = Path(".tools") / name
        if not directory.exists():
            directory.mkdir(parents=True)
            run("git", "init", str(directory))
            run("git", "-C", str(directory), "remote", "add", "origin", url)
            run("git", "-C", str(directory), "fetch", "--depth=1", "origin", commit)
            run("git", "-C", str(directory), "checkout", "--detach", "FETCH_HEAD")
        actual = subprocess.check_output(["git", "-C", str(directory), "rev-parse", "HEAD"], text=True).strip()
        if actual != commit:
            raise ValueError(f"{directory}: expected pinned commit {commit}, found {actual}; existing checkout preserved")
    run(python, "tools/fetch_compiler.py", "2.8.1")
    print("Local tool setup complete")


if __name__ == "__main__":
    main()
