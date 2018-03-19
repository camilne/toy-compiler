#ifndef PRINT_NODE_HPP
#define PRINT_NODE_HPP

#include <sstream>
#include <iomanip>
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

    virtual std::string toString(int indent = 0) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "PrintNode\n";
      if(exp)
        ss << exp->toString(indent + 1);
      return ss.str();
    }

    SyntaxTreeNode* getExp() const {
        return exp;
    }

private:
    SyntaxTreeNode* exp;
};

#endif
