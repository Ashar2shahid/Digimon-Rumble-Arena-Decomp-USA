"""Logical binary IDs remain stable; physical sources follow the JP repository layout."""
SOURCE_DIRS = {"main": "src/engine", "game": "src/battle", "title": "src/title", "movie": "src/movie", **{f"st{i:02d}": f"src/battle/stages/st{i:02d}" for i in range(10)}}
def source_dir(unit):
    return SOURCE_DIRS[unit]
