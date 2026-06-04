#include "hybridcompressor/Parser.h"
#include "hybridcompressor/ASTNode.h"
#include "hybridcompressor/Lexer.h"
#include <iostream>
#include <stdexcept>


hc::Parser::Parser(std::string input_source) {
    hc::Lexer lexer(input_source);

    while (true) {
        auto token = lexer.getNextToken();
        tokenQueue.push(token);
        if (token.type == hc::TokenType::END_OF_FILE)
            break;
    }
}


hc::ASTNode::Ptr hc::Parser::parse() {
    auto documentNode = parseDocument();
    return documentNode;
}

hc::ASTNode::Ptr hc::Parser::parseDocument() {
    auto root = std::make_unique<ASTNode>(NodeType::Document);
    while (!tokenQueue.empty()) {
        const Token &token = tokenQueue.front();

        switch (token.type) {
            case hc::TokenType::COMMENT:
                std::cout << "Found COMMENT tag: " << token.tagName.value_or("UNKNOWN") << std::endl;
                break;
            case hc::TokenType::ATTRIBUTE_NAME:
                std::cout << "Found ATTRIBUTE_NAME tag: " << token.tagName.value_or("UNKNOWN") << std::endl;

                break;
            case hc::TokenType::ATTRIBUTE_VALUE:
                std::cout << "Found ATTRIBUTE_VALUE tag: " << token.tagName.value_or("UNKNOWN") << std::endl;

                break;
            case hc::TokenType::DOCTYPE:
                std::cout << "Found DOCTYPE tag: " << token.tagName.value_or("UNKNOWN") << std::endl;

                break;
            case hc::TokenType::END_OF_FILE:
                std::cout << "Found END_OF_FILE" << std::endl;
                break;
            case hc::TokenType::END_TAG:
                std::cout << "Found END_TAG tag: " << token.tagName.value_or("UNKNOWN") << std::endl;

                break;
            case hc::TokenType::SELF_CLOSING_TAG: {


                break;
            }


            case hc::TokenType::START_TAG: {
                auto element = parseElement();
                root->addChild(std::move(element));

                break;
            }
            case hc::TokenType::TEXT: {
                std::cout << "Found TEXT: " << token.value << std::endl;

                auto textNode = std::make_unique<hc::ASTNode>(
                    hc::NodeType::Text,
                    token.value
                );

                root->addChild(std::move(textNode));
                break;
            }
            case hc::TokenType::UNKNOWN:
                std::cout << "Found UNKNOWN : " << token.tagName.value_or("UNKNOWN") << std::endl;

                break;
            default:
                break;
        }
        tokenQueue.pop();
    }
    std::cout << "Document children count: " << root->children.size() << std::endl;
    // std::cout << "Document children count: " << root->children << std::endl;

    return root;
}


void hc::Parser::setTokens(std::queue<Token> &tokens) {
    tokenQueue = tokens;
}


hc::ASTNode::Ptr hc::Parser::parseElement() {
    // Read the START_TAG
    auto token = tokenQueue.front();
    tokenQueue.pop();

    std::string tagName = token.value;


    std::cout << "Start Element: " << tagName << std::endl;

    auto elementNode = std::make_unique<hc::ASTNode>(
        hc::NodeType::Element,
        tagName
    );

    while (!tokenQueue.empty()) {
        auto nextToken = tokenQueue.front();

        if (nextToken.type == hc::TokenType::END_TAG) {
            if (nextToken.value == tagName) {
                // END of this element → pop and exit loop
                tokenQueue.pop();
                std::cout << "End Element: " << tagName << std::endl;
                break;
            }

            // END_TAG but not ours → pop and ignore
            tokenQueue.pop();
            continue;
        }


        if (nextToken.type == hc::TokenType::TEXT) {
            tokenQueue.pop();

            auto textNode = std::make_unique<hc::ASTNode>(
                hc::NodeType::Text,
                nextToken.value
            );

            elementNode->addChild(std::move(textNode));
            continue;
        }


        if (nextToken.type == hc::TokenType::START_TAG) {
            auto child = parseElement();
            elementNode->addChild(std::move(child));
            continue;
        }


        //Anything else → ignore
        tokenQueue.pop();
    }

    return elementNode;
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
