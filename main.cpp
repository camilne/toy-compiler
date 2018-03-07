#include <iostream>
#include "grammar.tab.h"

extern int yylex();

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
    else
        std::cout << "This input is valid." << std::endl;
    return result;
#endif
}
