#pragma once
#include <string>
#include <optional>

namespace hc {
    enum class TokenType {
        START_TAG,
        END_TAG,
        SELF_CLOSING_TAG,
        ATTRIBUTE_NAME,
        ATTRIBUTE_VALUE,
        TEXT,
        COMMENT,
        DOCTYPE,
        END_OF_FILE,
        UNKNOWN
    };

    class Token {
    public:
        TokenType type = TokenType::UNKNOWN;
        std::string value;

        std::optional<std::string> tagName;
        std::optional<std::string> attrName;
        std::optional<std::string> attrValue;

        size_t line = 1;
        size_t column = 1;
        size_t offset = 0;

    private:
        Token() = default;

    public:
        static Token makeText(const std::string &val, size_t line = 1, size_t column = 1, size_t offset = 0) {
            Token t;
            t.type = TokenType::TEXT;
            t.value = val;
            t.line = line;
            t.column = column;
            t.offset = offset;
            return t;
        }

        static Token makeComment(const std::string &val, size_t line = 1, size_t column = 1, size_t offset = 0) {
            Token t;
            t.type = TokenType::COMMENT;
            t.value = val;
            t.line = line;
            t.column = column;
            t.offset = offset;
            return t;
        }

        static Token makeDoctype(const std::string &val, size_t line = 1, size_t column = 1, size_t offset = 0) {
            Token t;
            t.type = TokenType::DOCTYPE;
            t.value = val;
            t.line = line;
            t.column = column;
            t.offset = offset;
            return t;
        }

        static Token makeTag(TokenType type, const std::string &tagName,
                             size_t line = 1, size_t column = 1, size_t offset = 0) {
            Token t;
            t.type = type; // START_TAG, END_TAG, SELF_CLOSING_TAG
            t.tagName = tagName;
            t.line = line;
            t.column = column;
            t.offset = offset;
            return t;
        }

        static Token makeAttribute(const std::string &name, const std::string &val = "",
                                   size_t line = 1, size_t column = 1, size_t offset = 0) {
            Token t;
            t.type = TokenType::ATTRIBUTE_NAME;
            t.attrName = name;
            if (!val.empty()) {
                t.attrValue = val;
            }
            t.line = line;
            t.column = column;
            t.offset = offset;
            return t;
        }

        static Token makeEOF(size_t line = 1, size_t column = 1, size_t offset = 0) {
            Token t;
            t.type = TokenType::END_OF_FILE;
            t.line = line;
            t.column = column;
            t.offset = offset;
            return t;
        }
    };
}
