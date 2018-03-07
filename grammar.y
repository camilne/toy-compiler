%{
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

int yylex(void);
void yyerror(char const*);
%}

%union {
    int             INT;
    const char*     STRING;
}

%token <STRING> IDENTIFIER
%token <INT> INTEGER
%token SEMICOLON OP_PLUS OP_MINUS;

%%

statements:
    statements statement                        {}
    | %empty

statement:
    expression SEMICOLON                        {}

expression:
    IDENTIFIER                                  { std::cout << "Identifier: " << $1 << std::endl; }

%%

void yyerror(char const* msg) {
    printf("Error: %s\n", msg);
    exit(1);
}
