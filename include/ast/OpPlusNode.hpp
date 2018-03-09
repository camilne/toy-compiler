#ifndef OP_PLUS_NODE
#define OP_PLUS_NODE

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class OpPlusNode : public SyntaxTreeNode {
public:
    OpPlusNode(SyntaxTreeNode* leftExp, SyntaxTreeNode* rightExp)
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
