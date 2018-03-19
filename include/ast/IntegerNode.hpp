#ifndef INTEGER_NODE_HPP
#define INTEGER_NODE_HPP

#include <sstream>
#include <iomanip>
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

    virtual std::string toString(int indent) const {
      std::stringstream ss;
      ss << std::setw(indent) << " " << "IntegerNode\n";
      ss << std::setw(indent + 1) << " " << value << "\n";
      return ss.str();
    }

    int getValue() const {
        return value;
    }

private:
    int value;
};

#endif
