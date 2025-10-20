#pragma once

#include <queue>

#include "Token.h"
#include <string>

namespace hc {
    class Lexer {
    public:
        explicit Lexer(std::string input_source);
        Token getNextToken();
        private:
        std::string source;
        size_t position = 0;
        char peek(size_t offset = 0) const;
        void advance(size_t count = 1);
        Token readText();
        Token readTag();
        std::string readAttributeName();
        std::string readAttributeValue();
        void skipWhitespace();

    private:
            std::queue<Token> tokenQueue;


    };
}
