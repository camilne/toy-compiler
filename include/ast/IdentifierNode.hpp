#ifndef IDENTIFIER_NODE_HPP
#define IDENTIFIER_NODE_HPP

#include <sstream>
#include <iomanip>
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

    virtual std::string toString(int indent) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "IdentifierNode\n";
      ss << std::setw(indent + 1) << " " << name << "\n";
      return ss.str();
    }

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
};

#endif
