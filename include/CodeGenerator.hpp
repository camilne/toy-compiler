#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include "SyntaxTree.ih"

class CodeGenerator {
public:
    explicit CodeGenerator(SyntaxTree* ast)
        : ast(ast)
    {}

    std::string generate();
private:
    SyntaxTree* ast;
};

#endif
