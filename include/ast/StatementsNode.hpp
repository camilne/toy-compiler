#ifndef STATEMENTS_NODE_HPP
#define STATEMENTS_NODE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class StatementsNode : public SyntaxTreeNode {
public:
    StatementsNode(SyntaxTreeNode* statements, SyntaxTreeNode* statement)
        : statements(statements), statement(statement)
    {}

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    SyntaxTreeNode* getStatements() const {
        return statements;
    }

    SyntaxTreeNode* getStatement() const {
        return statement;
    }

private:
    SyntaxTreeNode* statements;
    SyntaxTreeNode* statement;
};

#endif
