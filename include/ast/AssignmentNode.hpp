#ifndef ASSIGNMENT_NODE_HPP
#define ASSIGNMENT_NODE_HPP

#include <sstream>
#include <iomanip>
#include "ast/SyntaxTreeNode.hpp"
#include "ast/IdentifierNode.hpp"
#include "generator/IGenerator.hpp"

class AssignmentNode : public SyntaxTreeNode {
public:
    AssignmentNode(IdentifierNode* lhs, SyntaxTreeNode* rhs)
        : lhs(lhs), rhs(rhs)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    virtual std::string toString(int indent) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "AssignmentNode\n";
      if(lhs)
        ss << lhs->toString(indent + 1);
      if(rhs)
        ss << rhs->toString(indent + 1);
      return ss.str();
    }

    IdentifierNode* getIdentifier() const {
        return lhs;
    }

    SyntaxTreeNode* getExpression() const {
        return rhs;
    }

private:
    IdentifierNode* lhs;
    SyntaxTreeNode* rhs;
};

#endif
