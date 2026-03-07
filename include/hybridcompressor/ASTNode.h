#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

namespace hc {
    enum class NodeType {
        Document,
        Element,
        Text,
        Comment
    };

    struct Attribute {
        std::string name;
        std::string value;
    };

    class ASTNode {
    public:
        using Ptr = std::unique_ptr<ASTNode>;
        using Children = std::vector<Ptr>;

        NodeType type;
        std::string value;
        std::vector<Attribute> attributes;
        Children children;
        ASTNode *parent = nullptr;

        explicit ASTNode(NodeType nodeType, std::string nodeValue = "")
            : type(nodeType), value(std::move(nodeValue)) {
        }

        void addChild(Ptr child) {
            if (!child) {
                return;
            }

            child->parent = this;
            children.push_back(std::move(child));
        }

        void addAttribute(std::string name, std::string value) {
            attributes.push_back({std::move(name), std::move(value)});
        }

        bool isDocument() const {
            return type == NodeType::Document;
        }

        bool isElement() const {
            return type == NodeType::Element;
        }

        bool isText() const {
            return type == NodeType::Text;
        }

        bool isComment() const {
            return type == NodeType::Comment;
        }
    };
}
