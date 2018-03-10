#ifndef IDENTIFIER_NODE_HPP
#define IDENTIFIER_NODE_HPP

#include <string>
#include "ast/SyntaxTreeNode.hpp"
#include "generator/IGenerator.hpp"

class IdentifierNode : public SyntaxTreeNode {
public:
    explicit IdentifierNode(std::string name)
        : name(name)
    {}

    virtual std::string toCode() const;

    virtual void accept(IGenerator& generator) {
        generator.generate(*this);
    }

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
};

#endif
