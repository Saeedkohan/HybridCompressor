import unittest
import sys, os

sys.path.append(os.path.abspath("python"))
from hybridcompressor._core import Lexer, TokenType


class TestLexer(unittest.TestCase):

    def _get_all_tokens(self, html_str):
        lexer = Lexer(html_str)
        tokens = []
        while True:
            token = lexer.get_next_token()
            if token.type == TokenType.END_OF_FILE:
                break
            tokens.append(token)
        return tokens

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
    def test_comment(self):
        html = "<!-- this is a comment -->"
        tokens=self._get_all_tokens(html)
        self.assertEqual(len(tokens),1)
        self.assertEqual(tokens[0].type,TokenType.COMMENT)
        self.assertEqual(tokens[0].value," this is a comment ")
    def test_self_closing_tag(self):
        html = "<img />"
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.SELF_CLOSING_TAG)
        self.assertEqual(tokens[0].value, "img")
    def test_attribute_with_value(self):
        html = '<a href="https://example.com">'
        tokens=self._get_all_tokens(html)
        self.assertEqual(len(tokens),3)
        self.assertEqual(tokens[0].type, TokenType.START_TAG)
        self.assertEqual(tokens[0].value, "a")
        self.assertEqual(tokens[1].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[1].value, "href")
        self.assertEqual(tokens[2].type, TokenType.ATTRIBUTE_VALUE)
        self.assertEqual(tokens[2].value, "https://example.com")
    def test_attribute_without_value(self):
        html = "<input disabled>"
        tokens=self._get_all_tokens(html)
        self.assertEqual(len(tokens),2)
        self.assertEqual(tokens[0].type, TokenType.START_TAG)
        self.assertEqual(tokens[0].value, "input")
        self.assertEqual(tokens[1].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[1].value, "disabled")

    def test_mixed_attributes(self):
        html = '<div class="container" id="main" hidden>'
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 6)

        # START_TAG
        self.assertEqual(tokens[0].type, TokenType.START_TAG)
        self.assertEqual(tokens[0].value, "div")

        # class="container"
        self.assertEqual(tokens[1].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[1].value, "class")
        self.assertEqual(tokens[2].type, TokenType.ATTRIBUTE_VALUE)
        self.assertEqual(tokens[2].value, "container")

        # id="main"
        self.assertEqual(tokens[3].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[3].value, "id")
        self.assertEqual(tokens[4].type, TokenType.ATTRIBUTE_VALUE)
        self.assertEqual(tokens[4].value, "main")

        # hidden
        self.assertEqual(tokens[5].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[5].value, "hidden")

    def test_empty_input(self):
        html = ""
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 0)

    def test_attribute_with_single_quotes(self):
        html = "<img src='logo.png'>"
        tokens = self._get_all_tokens(html)
        self.assertEqual(len(tokens), 3)
        self.assertEqual(tokens[0].type, TokenType.START_TAG)
        self.assertEqual(tokens[0].value, "img")
        self.assertEqual(tokens[1].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[1].value, "src")
        self.assertEqual(tokens[2].type, TokenType.ATTRIBUTE_VALUE)
        self.assertEqual(tokens[2].value, "logo.png")

    def test_attribute_value_with_spaces_and_quotes(self):
        html = '<p title="Hello \'world\'">Text</p>'
        tokens = self._get_all_tokens(html)
        # tokens : START_TAG(p), ATTR_NAME(title), ATTR_VALUE(Hello 'world'), TEXT(Text), END_TAG(p)
        self.assertEqual(len(tokens), 5)
        self.assertEqual(tokens[0].type, TokenType.START_TAG)
        self.assertEqual(tokens[0].value, "p")
        self.assertEqual(tokens[1].type, TokenType.ATTRIBUTE_NAME)
        self.assertEqual(tokens[1].value, "title")
        self.assertEqual(tokens[2].type, TokenType.ATTRIBUTE_VALUE)
        self.assertEqual(tokens[2].value, "Hello 'world'")
        self.assertEqual(tokens[3].type, TokenType.TEXT)
        self.assertEqual(tokens[3].value, "Text")
        self.assertEqual(tokens[4].type, TokenType.END_TAG)
        self.assertEqual(tokens[4].value, "p")

    def test_nested_tags(self):
        html = "<div><p>Hello</p></div>"
        tokens = self._get_all_tokens(html)
        expected = [
            (TokenType.START_TAG, "div"),
            (TokenType.START_TAG, "p"),
            (TokenType.TEXT, "Hello"),
            (TokenType.END_TAG, "p"),
            (TokenType.END_TAG, "div"),
        ]
        self.assertEqual(len(tokens), len(expected))
        for i, (exp_type, exp_value) in enumerate(expected):
            self.assertEqual(tokens[i].type, exp_type)
            self.assertEqual(tokens[i].value, exp_value)
    def test_realistic_html_snippet(self):
        html = '<!DOCTYPE html><html><head><title>Test</title></head><body><div class="container">Hello <!-- comment --> world</div></body></html>'
        tokens = self._get_all_tokens(html)
        self.assertGreater(len(tokens), 0)


if __name__ == '__main__':
    unittest.main()
