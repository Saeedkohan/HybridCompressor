#include "hybridcompressor/Lexer.h"

hc::Token hc::Lexer::getNextToken() {
    if (peek() == '\0') {
        return hc::Token(TokenType::END_OF_FILE, "");
    }
    if (peek() == '<') {
        return readTag();
    } else {
        return readText();
    }
}

char hc::Lexer::peek(size_t offset) const {
    if (offset + position >= source.size()) {
        return '\0';
    }
    return source[offset + position];
}

void hc::Lexer::advance(size_t count) {
    position += count;
    if (position > source.size()) {
        position = source.size();
    }
}

hc::Token hc::Lexer::readText() {
    size_t start = position;
    while (peek() != '<' && peek() != '\0') {
        advance();
    }
    std::string text = source.substr(start, position - start);
    return hc::Token(TokenType::TEXT, text);
}
hc::Token hc::Lexer::readTag() {
    advance();

    if (peek(0) == '!' && peek(1) == '-' && peek(2) == '-') {
        advance(3);
        size_t start = position;
        while (!(peek(0) == '-' && peek(1) == '-' && peek(2) == '>') && peek() != '\0') {
            advance();
        }
        std::string text = source.substr(start, position - start);
        if (peek(0) == '-' && peek(1) == '-' && peek(2) == '>') {
            advance(3);
        }
        return Token(TokenType::COMMENT, text);
    }

    if (peek() == '/') {
        advance();
        size_t start = position;
        while (peek() != '>' && peek() != '\0') {
            advance();
        }
        std::string tagName = source.substr(start, position - start);
        if (peek() == '>') advance();
        return Token(TokenType::END_TAG, tagName);
    }

    size_t start = position;
    while (peek() != '>' && peek() != '\0') {
        advance();
    }
    std::string tagName = source.substr(start, position - start);
    if (peek() == '>') advance();
    return Token(TokenType::START_TAG, tagName);
}
