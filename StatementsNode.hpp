#ifndef STATEMENTS_NODE_HPP
#define STATEMENTS_NODE_HPP

#include "SyntaxTree.hpp"

class StatementsNode : public SyntaxTree::SyntaxTreeNode {
public:
    StatementsNode(SyntaxTree::SyntaxTreeNode* statements, SyntaxTree::SyntaxTreeNode* statement)
        : statements(statements), statement(statement)
    {}

    virtual std::string toCode() const;
private:
    SyntaxTree::SyntaxTreeNode* statements;
    SyntaxTree::SyntaxTreeNode* statement;
};

#endif
