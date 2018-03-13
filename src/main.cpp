#include <iostream>
#include "../generated/grammar.tab.h"
#include "ast/SyntaxTree.hpp"
#include "generator/MipsGenerator.hpp"

extern int yylex();
extern SyntaxTree* ast;

//#define LEXER_OUTPUT

int main() {
#ifdef LEXER_OUTPUT
    while(int token = yylex()) {
        std::cout << "Token: " << token << std::endl;
    }
    return 0;
#else
    int result = yyparse();
    if(result)
        std::cout << "This input is invalid." << std::endl;
    else {
        MipsGenerator generator;
        ast->accept(generator);

        generator.optimize();

        std::cout << generator.getCode() << std::endl;
    }

    return result;
#endif
}
