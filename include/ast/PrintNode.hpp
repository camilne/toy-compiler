#ifndef PRINT_NODE_HPP
#define PRINT_NODE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class PrintNode : public SyntaxTreeNode {
public:
    PrintNode(SyntaxTreeNode* exp)
        : exp(exp)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    SyntaxTreeNode* getExp() const {
        return exp;
    }

private:
    SyntaxTreeNode* exp;
};

#endif
