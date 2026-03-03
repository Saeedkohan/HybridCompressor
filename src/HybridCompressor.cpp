#include "hybridcompressor/HybridCompressor.h"
#include <iostream>
#include <cctype>

namespace hc {
    std::string HybridCompressor::compress(const std::string &input_html) {
        std::string pendingTag;
        std::string lastAttrName;
        std::vector<std::string> pendingAttrs;
        bool isSelfClosing = false;

        Lexer lexer(input_html);
        std::string output;

        auto flushPendingTag = [&]() {
            if (!pendingTag.empty()) {
                output += '<' + pendingTag;
                for (const auto &attr: pendingAttrs) {
                    output += ' ' + attr;
                }
                if (isSelfClosing) {
                    output += "/>";
                } else {
                    output += '>';
                }
                pendingTag.clear();
                pendingAttrs.clear();
                lastAttrName.clear();
                isSelfClosing = false;
            }
        };

        while (true) {
            Token token = lexer.getNextToken();
            if (token.type == TokenType::END_OF_FILE) {
                flushPendingTag();
                break;
            }

            if (token.type != TokenType::ATTRIBUTE_NAME &&
                token.type != TokenType::ATTRIBUTE_VALUE) {
                flushPendingTag();
            }

            if (token.type == TokenType::START_TAG) {
                pendingTag = token.value;
                isSelfClosing = false;
            } else if (token.type == TokenType::SELF_CLOSING_TAG) {
                pendingTag = token.value;
                isSelfClosing = true;
            } else if (token.type == TokenType::END_TAG) {
                output += "</" + token.value + ">";
            } else if (token.type == TokenType::ATTRIBUTE_NAME) {
                lastAttrName = token.value;
            } else if (token.type == TokenType::ATTRIBUTE_VALUE) {
                pendingAttrs.push_back(lastAttrName + "=\"" + token.value + "\"");
                lastAttrName.clear();
            } else if (token.type == TokenType::TEXT) {
                output += minifyText(token.value);
            }
        }
        return output;
    }


    std::string HybridCompressor::minifyText(const std::string &text) {
        std::string result;
        result.reserve(text.size());

        bool lastWasSpace = false;

        for (unsigned char c : text) {
            if (std::isspace(c)) {
                if (!lastWasSpace && !result.empty()) {
                    result += ' ';
                    lastWasSpace = true;
                }
            } else {
                result += c;
                lastWasSpace = false;
            }
        }

        if (!result.empty() && result.back() == ' ')
            result.pop_back();

        return result;
    }
} // namespace hc
