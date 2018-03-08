#ifndef OP_PLUS_NODE
#define OP_PLUS_NODE

#include "SyntaxTree.hpp"

class OpPlusNode : public SyntaxTree::SyntaxTreeNode {
public:
    OpPlusNode(SyntaxTree::SyntaxTreeNode* leftExp, SyntaxTree::SyntaxTreeNode* rightExp)
        : leftExp(leftExp), rightExp(rightExp)
    {}

    std::string toCode() const;

private:
    SyntaxTree::SyntaxTreeNode* leftExp;
    SyntaxTree::SyntaxTreeNode* rightExp;
};

#endif
