#ifndef SYNTAX_TREE_NODE_HPP
#define SYNTAX_TREE_NODE_HPP

#include <string>

class IGenerator;

class SyntaxTreeNode {
public:
    virtual void accept(IGenerator& generator) = 0;
    virtual std::string toString(int indent = 0) const = 0;
    virtual std::string toCode() const = 0;
};

#endif
