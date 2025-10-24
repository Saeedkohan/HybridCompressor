from enum import Enum

class TokenType(Enum):
    START_TAG = 0
    END_TAG = 1
    TEXT = 2
    COMMENT = 3
    ATTRIBUTE = 4
    ATTRIBUTE_NAME = 5
    ATTRIBUTE_VALUE = 6
    SELF_CLOSING_TAG = 7
    END_OF_FILE = 8
    UNKNOWN = 9

class Token:
    type: TokenType
    value: str
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...

class Lexer:
    def __init__(self, input_source: str) -> None: ...
    def get_next_token(self) -> Token: ...