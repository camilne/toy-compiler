#ifndef STATEMENTS_NODE_HPP
#define STATEMENTS_NODE_HPP

#include <sstream>
#include <iomanip>
#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class StatementsNode : public SyntaxTreeNode {
public:
    StatementsNode(SyntaxTreeNode* statements, SyntaxTreeNode* statement)
        : statements(dynamic_cast<StatementsNode*>(statements)),
          statement(statement)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    virtual std::string toString(int indent = 0) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "StatementsNode\n";
      if(statements)
        ss << statements->toString(indent + 1);
      if(statement)
        ss << statement->toString(indent + 1);
      return ss.str();
    }

    StatementsNode* getStatements() const {
        return statements;
    }

    SyntaxTreeNode* getStatement() const {
        return statement;
    }

    template <typename T>
    T getStatementAs() const {
      return dynamic_cast<T>(statement);
    }

private:
    StatementsNode* statements;
    SyntaxTreeNode* statement;
};

#endif
