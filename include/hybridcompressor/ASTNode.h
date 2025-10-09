#pragma once
#include <vector>
#include <memory>
#include <string>

namespace hc {
    enum NodeType {
        DOCUMENT,
        ELEMENT,
        TEXT,
        COMMENT,
    };
    class ASTNode {
        public:
        using Ptr = std::shared_ptr<ASTNode>;
        NodeType type;
        std::string content;
        std::vector<Ptr> children;
        ASTNode* parent=nullptr;
        ASTNode(NodeType type,std::string content=""):type(type),content(std::move(content)) {}

        void addChild(Ptr child) {
            child->parent = this;
            children.push_back(std::move(child));
        }
        virtual ~ASTNode() = default;
    };
}
