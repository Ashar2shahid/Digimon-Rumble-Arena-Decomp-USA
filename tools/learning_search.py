"""Find relevant sections of the decompilation learnings journal.

Usage: python tools/learning_search.py "pointer register" [--limit 3]
"""

import argparse
from pathlib import Path
import re


DEFAULT_JOURNAL = Path(__file__).resolve().parent.parent / "docs/DECOMPILATION_LEARNINGS.md"
MAX_EXCERPT_CHARS = 1800
GENERIC_WORDS = frozenset(
    "a an and are as at be by do does for from how in is it of on or the to "
    "what when where which with this that these those code decompilation "
    "function functions finding findings match matching".split()
)
WORD_RE = re.compile(r"[\w]+", re.UNICODE)
HEADING_RE = re.compile(r"^(#{2,6})[ \t]+(.+?)\s*#*\s*$", re.MULTILINE)


def _sections(text):
    """Yield H2 findings; use H3 when a journal has no H2 headings."""
    headings = list(HEADING_RE.finditer(text))
    if not headings:
        return
    level = min(len(match.group(1)) for match in headings)
    primary = [match for match in headings if len(match.group(1)) == level]
    for index, heading in enumerate(primary):
        end = primary[index + 1].start() if index + 1 < len(primary) else len(text)
        yield heading.group(2).strip(), text[heading.start():end].strip()


def _excerpt(section):
    if len(section) <= MAX_EXCERPT_CHARS:
        return section
    prefix = section[: MAX_EXCERPT_CHARS - len("\n[truncated]")]
    boundary = prefix.rfind("\n")
    if boundary > MAX_EXCERPT_CHARS // 2:
        prefix = prefix[:boundary]
    return prefix.rstrip() + "\n[truncated]"


def search_sections(text, query, limit=3):
    """Return up to ``limit`` ranked Markdown finding excerpts.

    Search treats journal content only as text. Ties retain journal order.
    """
    if limit <= 0:
        return []
    tokens = [word.casefold() for word in WORD_RE.findall(query)
              if word.casefold() not in GENERIC_WORDS]
    if not tokens:
        return []
    terms = tuple(dict.fromkeys(tokens))
    phrase = " ".join(query.casefold().split())
    ranked = []
    for order, (title, section) in enumerate(_sections(text)):
        title_lower = title.casefold()
        section_lower = section.casefold()
        title_words = set(WORD_RE.findall(title_lower))
        body_words = WORD_RE.findall(section_lower)
        title_hits = sum(term in title_words for term in terms)
        body_hits = sum(min(body_words.count(term), 3) for term in terms)
        phrase_in_title = len(terms) > 1 and phrase in title_lower
        phrase_in_body = len(terms) > 1 and phrase in section_lower
        if not (title_hits or body_hits or phrase_in_title or phrase_in_body):
            continue
        score = 40 * phrase_in_title + 12 * phrase_in_body + 10 * title_hits + 2 * body_hits
        ranked.append((-score, order, _excerpt(section)))
    ranked.sort()
    return [section for _, _, section in ranked[:limit]]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("query", help="words or phrase to find")
    parser.add_argument("--limit", type=int, default=3, help="maximum findings to show (default: 3)")
    parser.add_argument("--journal", type=Path, default=DEFAULT_JOURNAL,
                        help="Markdown journal path")
    args = parser.parse_args(argv)
    if args.limit < 1:
        parser.error("--limit must be positive")
    try:
        journal = args.journal.read_text(encoding="utf-8")
    except OSError as error:
        parser.error(f"cannot read journal: {error}")
    sections = search_sections(journal, args.query, args.limit)
    print("\n\n---\n\n".join(sections) if sections else "No matching findings.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
