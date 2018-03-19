#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include "ast/SyntaxTreeNode.hpp"
#include "ast/InitNode.hpp"
#include "generator/MipsGenerator.hpp"

class SyntaxTree {
public:
    explicit SyntaxTree(SyntaxTreeNode* root)
        : root(dynamic_cast<InitNode*>(root))
    {}

    void accept(IGenerator& generator) {
        root->accept(generator);
    }

    std::string toString() const {
      return root->toString();
    }

    const InitNode* getRoot() const {
      return root;
    }

private:
    InitNode* root;
};

#endif
