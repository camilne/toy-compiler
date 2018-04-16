#ifndef OP_LESS_THAN_EQUAL_NODE_HPP
#define OP_LESS_THAN_EQUAL_NODE_HPP

#include <sstream>
#include <iomanip>
#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class OpLessThanEqualNode : public SyntaxTreeNode {
public:
    OpLessThanEqualNode(SyntaxTreeNode* leftExp, SyntaxTreeNode* rightExp)
        : leftExp(leftExp), rightExp(rightExp)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    virtual std::string toString(int indent = 0) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "OpLessThanEqualNode\n";
      if(leftExp)
        ss << leftExp->toString(indent + 1);
      if(rightExp)
        ss << rightExp->toString(indent + 1);
      return ss.str();
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