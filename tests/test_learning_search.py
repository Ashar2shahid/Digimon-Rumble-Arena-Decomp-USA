"""Ranked learning search uses section boundaries and avoids journal dumps."""
from pathlib import Path
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from io import StringIO

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
from learning_search import MAX_EXCERPT_CHARS, main, search_sections


JOURNAL = """# Learnings

Introduction unrelated to findings.

## Register scheduling
The pointer load moves before the store.
### Example
Keep this example inside the register finding.

## Pointer register ordering
An exact pointer register phrase explains the failure.

## Compiler range
One compiler range applies to this function.

## Another compiler range
The compiler changed, but the range stayed stable.
"""


class LearningSearchTests(unittest.TestCase):
    def test_sections_preserve_nested_heading_and_stop_at_next_finding(self):
        result = search_sections(JOURNAL, "scheduling")
        self.assertEqual(len(result), 1)
        self.assertIn("### Example", result[0])
        self.assertNotIn("## Pointer register ordering", result[0])

    def test_exact_multiword_title_phrase_outranks_body_tokens(self):
        result = search_sections(JOURNAL, "pointer register")
        self.assertTrue(result[0].startswith("## Pointer register ordering"))
        self.assertTrue(result[1].startswith("## Register scheduling"))

    def test_equal_scores_keep_journal_order(self):
        result = search_sections(JOURNAL, "compiler range")
        self.assertTrue(result[0].startswith("## Compiler range"))
        self.assertTrue(result[1].startswith("## Another compiler range"))

    def test_empty_and_generic_queries_return_nothing(self):
        self.assertEqual(search_sections(JOURNAL, "  "), [])
        self.assertEqual(search_sections(JOURNAL, "the function and code"), [])
        self.assertEqual(search_sections(JOURNAL, "compiler", limit=0), [])

    def test_limit_and_excerpt_cap(self):
        self.assertEqual(len(search_sections(JOURNAL, "compiler", limit=1)), 1)
        long_text = "## Compiler\n" + "compiler detail\n" * 250
        result = search_sections(long_text, "compiler")
        self.assertLessEqual(len(result[0]), MAX_EXCERPT_CHARS)
        self.assertTrue(result[0].endswith("[truncated]"))

    def test_cli_uses_supplied_journal(self):
        temporary_root = Path(__file__).absolute().parent.parent / "analysis/test-temp"
        temporary_root.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=temporary_root) as directory:
            path = Path(directory) / "journal.md"
            path.write_text(JOURNAL, encoding="utf-8")
            output = StringIO()
            with redirect_stdout(output):
                self.assertEqual(main(["pointer register", "--limit", "1", "--journal", str(path)]), 0)
            self.assertIn("## Pointer register ordering", output.getvalue())
            self.assertNotIn("## Register scheduling", output.getvalue())


if __name__ == "__main__":
    unittest.main()
