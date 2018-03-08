#ifndef OP_MINUS_NODE
#define OP_MINUS_NODE

#include "ast/SyntaxTree.hpp"

class OpMinusNode : public SyntaxTree::SyntaxTreeNode {
public:
    OpMinusNode(SyntaxTree::SyntaxTreeNode* leftExp, SyntaxTree::SyntaxTreeNode* rightExp)
        : leftExp(leftExp), rightExp(rightExp)
    {}

    std::string toCode() const;

private:
    SyntaxTree::SyntaxTreeNode* leftExp;
    SyntaxTree::SyntaxTreeNode* rightExp;
};

#endif
