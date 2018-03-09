#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "generator/MipsGenerator.hpp"

class SyntaxTree {
public:
    explicit SyntaxTree(SyntaxTreeNode* root)
        : root(root)
    {}

    void accept(IGenerator& generator) {
        root->accept(generator);
    }

private:
    SyntaxTreeNode* root;
};

#endif
