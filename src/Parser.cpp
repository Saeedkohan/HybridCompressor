#include "hybridcompressor/Parser.h"
#include "hybridcompressor/ASTNode.h"
#include <stdexcept>

void hc::Parser::setTokens(std::queue<Token> &tokens) {
    throw std::runtime_error("Not Implemented yet");
}

hc::ASTNode::Ptr hc::Parser::parse() {
    throw std::runtime_error("Parser::parse() not implemented yet.");
}

hc::ASTNode::Ptr hc::Parser::parseDocument() {
    throw std::runtime_error("Parser::parseDocument() not implemented yet.");
}

hc::ASTNode::Ptr hc::Parser::parseElement() {
    throw std::runtime_error("Parser::parseElement() not implemented yet.");
}

hc::ASTNode::Ptr hc::Parser::parseText() {
    throw std::runtime_error("Parser::parseText() not implemented yet.");
}

hc::ASTNode::Ptr hc::Parser::parseComment() {
    throw std::runtime_error("Parser::parseComment() not implemented yet.");
}

std::string hc::Parser::consume(TokenType type) {
    throw std::runtime_error("Parser::consume() not implemented yet.");
}

hc::Token hc::Parser::peek() {
    throw std::runtime_error("Parser::peek() not implemented yet.");
}

hc::Token hc::Parser::advance() {
    throw std::runtime_error("Parser::advance() not implemented yet.");
}

void hc::Parser::skipWhitespace() {
    throw std::runtime_error("Parser::skipWhitespace() not implemented yet.");
}

std::map<std::string, std::string> hc::Parser::parseAttributes() {
    throw std::runtime_error("Parser::parseAttributes() not implemented yet.");
}
