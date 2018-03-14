#ifndef WHILE_NODE_HPP
#define WHILE_NODE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class WhileNode : public SyntaxTreeNode {
public:
    WhileNode(SyntaxTreeNode* exp, SyntaxTreeNode* statements)
        : exp(exp), statements(statements)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    SyntaxTreeNode* getExpression() const {
        return exp;
    }

    SyntaxTreeNode* getStatements() const {
        return statements;
    }

private:
    SyntaxTreeNode* exp;
    SyntaxTreeNode* statements;
};

#endif
