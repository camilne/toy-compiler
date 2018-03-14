#ifndef ASSIGNMENT_NODE_HPP
#define ASSIGNMENT_NODE_HPP

#include <string>
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
