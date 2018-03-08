#ifndef INTEGER_NODE_HPP
#define INTEGER_NODE_HPP

#include "ast/SyntaxTree.hpp"

class IntegerNode : public SyntaxTree::SyntaxTreeNode {
public:
    explicit IntegerNode(int value)
        : value(value)
    {}

    virtual std::string toCode() const;

private:
    int value;
};

#endif
