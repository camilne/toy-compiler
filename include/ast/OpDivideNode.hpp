#ifndef OP_DIVIDE_NODE_HPP
#define OP_DIVIDE_NODE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class OpDivideNode : public SyntaxTreeNode {
public:
    OpDivideNode(SyntaxTreeNode* leftExp, SyntaxTreeNode* rightExp)
        : leftExp(leftExp), rightExp(rightExp)
    {}

    virtual std::string toCode() const;

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
