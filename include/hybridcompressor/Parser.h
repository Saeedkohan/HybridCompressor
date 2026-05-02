#pragma once

#include <queue>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "Token.h"
#include "ASTNode.h"
namespace hc {
    class Parser {
    public:
        explicit Parser(std::string input_source);
        void setTokens(std::queue<Token>& tokens);

        ASTNode::Ptr parse();

    private:
        ASTNode::Ptr parseDocument();
        ASTNode::Ptr parseElement();
        ASTNode::Ptr parseText();
        ASTNode::Ptr parseComment();
        std::string consume(TokenType type);
        Token peek();
        Token advance();
        void skipWhitespace();
        std::map<std::string, std::string> parseAttributes();

        std::queue<Token> tokenQueue;
    };
}
