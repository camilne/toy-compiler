#ifndef SYNTAX_TREE_NODE_HPP
#define SYNTAX_TREE_NODE_HPP

class IGenerator;

class SyntaxTreeNode {
public:
    virtual void accept(IGenerator& generator) = 0;
};

#endif
