#ifndef INIT_NODE_HPP
#define INIT_NODE_HPP

#include <sstream>
#include <iomanip>
#include "ast/SyntaxTreeNode.hpp"
#include "ast/StatementsNode.hpp"
#include "generator/IGenerator.hpp"

class InitNode : public SyntaxTreeNode {
public:
    InitNode(SyntaxTreeNode* statements)
        : statements(dynamic_cast<StatementsNode*>(statements))
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    virtual std::string toString(int indent = 0) const {
      std::stringstream ss;
      ss << std::setw(indent) << "InitNode\n";
      if(statements)
        ss << statements->toString(indent + 1);
      return ss.str();
    }

    StatementsNode* getStatements() const {
        return statements;
    }

private:
    StatementsNode* statements;
};

#endif
