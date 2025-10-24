import unittest
import sys, os

sys.path.append(os.path.abspath("python"))
from hybridcompressor._core import Lexer, TokenType


class TestLexer(unittest.TestCase):
    def test_simple_text(self):
        html = "hello world"
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.TEXT)
        self.assertEqual(tokens[0].value, "hello world")

    def test_start_tag(self):
        html = "<div>"
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.START_TAG)
        self.assertEqual(tokens[0].value, "div")

    def test_end_tag(self):
        html = "</p>"
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.END_TAG)
        self.assertEqual(tokens[0].value, "p")

    def _get_all_tokens(self, html_str):
        lexer = Lexer(html_str)
        tokens = []
        while True:
            token = lexer.get_next_token()
            if token.type == TokenType.END_OF_FILE:
                break
            tokens.append(token)
        return tokens


if __name__ == '__main__':
    unittest.main()
