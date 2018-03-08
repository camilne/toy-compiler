#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <string>

class SyntaxTree {
public:
    class SyntaxTreeNode {
    public:
        virtual std::string toCode() const = 0;
    };

    explicit SyntaxTree(SyntaxTreeNode* root)
        : root(root)
    {}

    std::string toCode() const {
        return root->toCode();
    }

private:
    SyntaxTreeNode* root;
};

#endif
