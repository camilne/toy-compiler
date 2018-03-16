#include <iostream>
#include "../generated/grammar.tab.h"
#include "ast/SyntaxTree.hpp"
#include "generator/MipsGenerator.hpp"
#include "Arguments.hpp"
#include <vector>

extern int yylex();
extern SyntaxTree* ast;

int main(int argc, char** argv) {
    bool verbose = false;

    Arguments arguments(argc, argv);
    arguments.registerFlag("-v", [&](){
        std::cout << "setting verbose" << std::endl;
        verbose = true;
    });
    arguments.process();

    int result = yyparse();
    if(result)
        std::cout << "This input is invalid." << std::endl;
    else {
        MipsGenerator generator(verbose);
        ast->accept(generator);

        generator.optimize();

        std::cout << generator.getCode() << std::endl;
    }

    return result;
}
