#include <iostream>
#include <memory>

#include "hybridcompressor/ASTNode.h"

using hc::ASTNode;
using hc::NodeType;

bool testBasicTree() {
    ASTNode document(NodeType::Document);

    auto div = std::make_unique<ASTNode>(NodeType::Element, "div");
    ASTNode* divPtr = div.get();

    div->addAttribute("class", "a");

    auto text = std::make_unique<ASTNode>(NodeType::Text, "hello");
    ASTNode* textPtr = text.get();

    div->addChild(std::move(text));
    document.addChild(std::move(div));

    if (!document.isDocument()) {
        std::cout << "[FAIL] basic_tree: root is not Document\n";
        return false;
    }

    if (document.children.size() != 1) {
        std::cout << "[FAIL] basic_tree: document should have exactly 1 child\n";
        return false;
    }

    if (!divPtr->isElement()) {
        std::cout << "[FAIL] basic_tree: first child is not Element\n";
        return false;
    }

    if (divPtr->value != "div") {
        std::cout << "[FAIL] basic_tree: element value should be 'div'\n";
        return false;
    }

    if (divPtr->attributes.size() != 1) {
        std::cout << "[FAIL] basic_tree: div should have exactly 1 attribute\n";
        return false;
    }

    if (divPtr->attributes[0].name != "class" || divPtr->attributes[0].value != "a") {
        std::cout << "[FAIL] basic_tree: attribute should be class=\"a\"\n";
        return false;
    }

    if (divPtr->children.size() != 1) {
        std::cout << "[FAIL] basic_tree: div should have exactly 1 child\n";
        return false;
    }

    if (!textPtr->isText()) {
        std::cout << "[FAIL] basic_tree: child of div is not Text\n";
        return false;
    }

    if (textPtr->value != "hello") {
        std::cout << "[FAIL] basic_tree: text value should be 'hello'\n";
        return false;
    }

    if (textPtr->parent != divPtr) {
        std::cout << "[FAIL] basic_tree: text parent is not div\n";
        return false;
    }

    if (divPtr->parent != &document) {
        std::cout << "[FAIL] basic_tree: div parent is not document\n";
        return false;
    }

    std::cout << "[PASS] basic_tree\n";
    return true;
}

int main() {
    int failedCount = 0;

    failedCount += !testBasicTree();

    if (failedCount == 0) {
        std::cout << "All AST tests passed.\n";
        return 0;
    }

    std::cout << failedCount << " AST test(s) failed.\n";
    return 1;
}