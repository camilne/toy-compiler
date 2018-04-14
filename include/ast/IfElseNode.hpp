#ifndef IF_ELSE_NODE_HPP
#define IF_ELSE_NODE_HPP

#include <sstream>
#include <iomanip>
#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class IfElseNode : public SyntaxTreeNode {
public:
    IfElseNode(SyntaxTreeNode* exp, SyntaxTreeNode* statements, SyntaxTreeNode* elseStatements)
        : exp(exp), statements(statements), elseStatements(elseStatements)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    virtual std::string toString(int indent = 0) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "IfElseNode\n";
      if(exp)
        ss << exp->toString(indent + 1);
      if(statements)
        ss << statements->toString(indent + 1);
      if(elseStatements)
        ss << elseStatements->toString(indent + 1);
      return ss.str();
    }

    SyntaxTreeNode* getExpression() const {
        return exp;
    }

    SyntaxTreeNode* getStatements() const {
        return statements;
    }

    SyntaxTreeNode* getElseStatements() const {
      return elseStatements;
    }

private:
    SyntaxTreeNode* exp;
    SyntaxTreeNode* statements;
    SyntaxTreeNode* elseStatements;
};

#endif
