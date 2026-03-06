#include <vector>
#include <string>
#include <iostream>

#include "hybridcompressor/Lexer.h"
#include "hybridcompressor/Token.h"

using hc::Lexer;
using hc::Token;
using hc::TokenType;

struct ExpectedToken {
    TokenType type;
    std::string value;
};

std::vector<ExpectedToken> tokenize(const std::string &input) {
    Lexer lexer(input);
    std::vector<ExpectedToken> tokens;

    while (true) {
        Token t = lexer.getNextToken();

        if (t.type == TokenType::END_OF_FILE) {
            break;
        }

        tokens.push_back({t.type, t.value});
    }

    return tokens;
}

bool runCase(const std::string &name, const std::string &input, const std::vector<ExpectedToken> &expected) {
    std::vector<ExpectedToken> got = tokenize(input);

    if (got.size() != expected.size()) {
        std::cout << "[FAIL] " << name << " token count mismatch\n";
        std::cout << "Expected: " << expected.size()
                << " Got: " << got.size() << "\n";
        return false;
    }

    for (size_t i = 0; i < expected.size(); ++i) {
        if (got[i].type != expected[i].type || got[i].value != expected[i].value) {
            std::cout << "[FAIL] " << name << " mismatch at index " << i << "\n";
            std::cout << "Expected: (" << static_cast<int>(expected[i].type)
                    << ", " << expected[i].value << ")\n";
            std::cout << "Got: (" << static_cast<int>(got[i].type)
                    << ", " << got[i].value << ")\n";
            return false;
        }
    }

    std::cout << "[PASS] " << name << "\n";
    return true;
}

int main() {
    int failedCount = 0;

    failedCount += !runCase("simple_div", "<div>hi</div>", {
                                {TokenType::START_TAG, "div"},
                                {TokenType::TEXT, "hi"},
                                {TokenType::END_TAG, "div"}
                            });

    failedCount += !runCase("attr_quoted", R"(<div class="a">x</div>)", {
                                {TokenType::START_TAG, "div"},
                                {TokenType::ATTRIBUTE_NAME, "class"},
                                {TokenType::ATTRIBUTE_VALUE, "a"},
                                {TokenType::TEXT, "x"},
                                {TokenType::END_TAG, "div"}
                            });

    failedCount += !runCase("attr_unquoted", "<input type=text>", {
                                {TokenType::START_TAG, "input"},
                                {TokenType::ATTRIBUTE_NAME, "type"},
                                {TokenType::ATTRIBUTE_VALUE, "text"}
                            });

    failedCount += !runCase("self_closing", "<br/>", {
                                {TokenType::SELF_CLOSING_TAG, "br"}
                            });
    failedCount += !runCase("comment", "<!--hello-->", {
                                {TokenType::COMMENT, "hello"}
                            });

    failedCount += !runCase("nested_text", "<div><span>ok</span></div>", {
                                {TokenType::START_TAG, "div"},
                                {TokenType::START_TAG, "span"},
                                {TokenType::TEXT, "ok"},
                                {TokenType::END_TAG, "span"},
                                {TokenType::END_TAG, "div"}
                            });

    if (failedCount == 0) {
        std::cout << "All lexer tests passed.\n";
        return 0;
    }

    std::cout << failedCount << " lexer test(s) failed.\n";
    return 1;
}
