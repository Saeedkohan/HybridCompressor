#include "hybridcompressor/Lexer.h"


hc::Lexer::Lexer(std::string input_source) : source(std::move(input_source)) {
}

hc::Token hc::Lexer::getNextToken() {
    if (!tokenQueue.empty()) {
        Token tok = tokenQueue.front();
        tokenQueue.pop();
        return tok;
    }


    if (peek() == '\0') {
        return Token(TokenType::END_OF_FILE, "");
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
        while (peek() != '>' && peek() != '\0') advance();
        std::string tagName = source.substr(start, position - start);
        if (peek() == '>') advance();
        return Token(TokenType::END_TAG, tagName);
    }


    size_t start = position;
    while (peek() != ' ' && peek() != '\t' && peek() != '\n' &&
           peek() != '/' && peek() != '>' && peek() != '\0') {
        advance();
    }
    std::string tagName = source.substr(start, position - start);


    skipWhitespace();
    while (peek() != '>' && peek() != '/' && peek() != '\0') {
        std::string attrName = readAttributeName();
        if (!attrName.empty()) {
            tokenQueue.push(Token(TokenType::ATTRIBUTE_NAME, attrName));
        }

        std::string attrValue = readAttributeValue();
        if (!attrValue.empty()) {
            tokenQueue.push(Token(TokenType::ATTRIBUTE_VALUE, attrValue));
        }

        skipWhitespace();
    }


    bool selfClosing = false;
    if (peek() == '/') {
        selfClosing = true;
        advance();
    }


    if (peek() == '>') advance();


    if (selfClosing) {
        return Token(TokenType::SELF_CLOSING_TAG, tagName);
    } else {
        return Token(TokenType::START_TAG, tagName);
    }
}


std::string hc::Lexer::readAttributeName() {
    skipWhitespace();
    size_t start = position;
    while (peek() != '=' && peek() != ' ' && peek() != '>' && peek() != '/' && peek() != '\0') {
        advance();
    }
    return source.substr(start, position - start);
}

std::string hc::Lexer::readAttributeValue() {
    skipWhitespace();

    if (peek() == '=') advance();

    skipWhitespace();

    char quote = '\0';
    if (peek() == '"' || peek() == '\'') {
        quote = peek();
        advance();
        size_t start = position;
        while (peek() != quote && peek() != '\0') {
            advance();
        }

        std::string value = source.substr(start, position - start);
        if (peek() == quote) advance();
        return value;
    }
    size_t start = position;
    while (peek() != ' ' && peek() != '>' && peek() != '/' && peek() != '\0') {
        advance();
    }
    return source.substr(start, position - start);
}

void hc::Lexer::skipWhitespace() {
    while (peek() == ' ' || peek() == '\t' || peek() == '\n' || peek() == '\r') {
        advance();
    }
}
