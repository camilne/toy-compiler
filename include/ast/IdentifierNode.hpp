#ifndef IDENTIFIER_NODE_HPP
#define IDENTIFIER_NODE_HPP

#include "ast/SyntaxTree.hpp"

class IdentifierNode : public SyntaxTree::SyntaxTreeNode {
public:
    explicit IdentifierNode(std::string name)
        : name(name)
    {}

    virtual std::string toCode() const;

private:
    std::string name;
};

#endif
