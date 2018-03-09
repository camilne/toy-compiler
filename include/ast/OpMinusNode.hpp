#ifndef OP_MINUS_NODE
#define OP_MINUS_NODE

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class OpMinusNode : public SyntaxTreeNode {
public:
    OpMinusNode(SyntaxTreeNode* leftExp, SyntaxTreeNode* rightExp)
        : leftExp(leftExp), rightExp(rightExp)
    {}

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    SyntaxTreeNode* getLeftExp() const {
        return leftExp;
    }

    SyntaxTreeNode* getRightExp() const {
        return rightExp;
    }

private:
    SyntaxTreeNode* leftExp;
    SyntaxTreeNode* rightExp;
};

#endif
