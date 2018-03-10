#ifndef INTEGER_NODE_HPP
#define INTEGER_NODE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class IntegerNode : public SyntaxTreeNode {
public:
    explicit IntegerNode(int value)
        : value(value)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    int getValue() const {
        return value;
    }

private:
    int value;
};

#endif
