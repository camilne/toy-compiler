#ifndef INIT_NODE_HPP
#define INIT_NODE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class InitNode : public SyntaxTreeNode {
public:
    InitNode(SyntaxTreeNode* statements)
        : statements(statements)
    {}

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    SyntaxTreeNode* getStatements() const {
        return statements;
    }

private:
    SyntaxTreeNode* statements;
};

#endif
