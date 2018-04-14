#ifndef IF_NODE_HPP
#define IF_NODE_HPP

#include <sstream>
#include <iomanip>
#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class IfNode : public SyntaxTreeNode {
public:
    IfNode(SyntaxTreeNode* exp, SyntaxTreeNode* statements)
        : exp(exp), statements(statements)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    virtual std::string toString(int indent = 0) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "IfNode\n";
      if(exp)
        ss << exp->toString(indent + 1);
      if(statements)
        ss << statements->toString(indent + 1);
      return ss.str();
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
