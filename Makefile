# USA SLUS_014.04; logical IDs remain main/game/title/movie/st00..st09.
.DEFAULT_GOAL := all
PYTHON ?= python
VERSION ?= us
ifneq ($(VERSION),us)
$(error supported VERSION is us)
endif
.PHONY: all generate compare report test worklist profiles
all:
	$(PYTHON) tools/verify.py
generate:
	$(PYTHON) tools/generate_game.py
compare:
	$(PYTHON) tools/verify.py --check
report:
	$(PYTHON) tools/game_progress.py --save --require-verified
test:
	$(PYTHON) -m unittest discover -s tests -v
worklist:
	$(PYTHON) tools/worklist.py --save
profiles:
	$(PYTHON) tools/profile_audit.py --save --summary
