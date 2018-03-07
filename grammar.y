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
%token SEMICOLON

%type <INT> statement
%type <INT> expression

%left OP_PLUS OP_MINUS

%%

statements:
    statements statement                        {}
    | %empty

statement:
    expression SEMICOLON                        { std::cout << "Expression value: " << $1 << std::endl; }

expression:
      expression OP_PLUS expression             { $$ = $1 + $3; }
    | expression OP_MINUS expression            { $$ = $1 - $3; }
    | IDENTIFIER                                { std::cout << "Identifier: " << $1 << std::endl; }
    | INTEGER                                   { std::cout << "Integer: " << $1 << std::endl; }

%%

void yyerror(char const* msg) {
    printf("Error: %s\n", msg);
    exit(1);
}
