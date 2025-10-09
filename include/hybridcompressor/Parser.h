#pragma once

#include "Lexer.h"
#include "ASTNode.h"
#include "Token.h"
#include <memory>

namespace hc {
    class Parser {
        public:
        explicit Parser(std::string input_source);
        ASTNode::Ptr parse();

    private:
        Lexer lexer;
        Token currentToken;

        void consume(TokenType expectedType);
        void getNextToken();

        ASTNode::Ptr parseElement();
        ASTNode::Ptr parseText();
    };
}