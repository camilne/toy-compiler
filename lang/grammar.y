%code requires{
#include "SyntaxTree.ih"
}

%{
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include "SyntaxTree.ih"

int yylex(void);
void yyerror(char const*);
extern char* yytext;

SyntaxTree* ast;
%}

%union {
    int                                 INT;
    const char*                         STRING;
    class SyntaxTree::SyntaxTreeNode*   NODE;
}

%type <NODE> statements
%type <NODE> statement
%type <NODE> expression

%token <STRING> IDENTIFIER
%token <INT> INTEGER
%token SEMICOLON

%left OP_PLUS OP_MINUS

%start init

%%

init:
    statements statement                        { ast = new SyntaxTree(new StatementsNode($1, $2)); }

statements:
    statements statement                        { $$ = new StatementsNode($1, $2); }
    | %empty                                    { $$ = nullptr; }

statement:
    expression SEMICOLON                        { $$ = $1; }

expression:
      expression OP_PLUS expression             { $$ = new OpPlusNode($1, $3); }
    | expression OP_MINUS expression            { $$ = new OpMinusNode($1, $3); }
    | IDENTIFIER                                { $$ = new IdentifierNode($1); }
    | INTEGER                                   { $$ = new IntegerNode($1); }

%%

void yyerror(char const* msg) {
    printf("Error: %s\n", msg);
    exit(1);
}
