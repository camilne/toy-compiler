%define parse.error verbose

%code requires{
    #include "ast/SyntaxTree.ih"
}

%{
    #include <stdio.h>
    #include <stdlib.h>

    #include <iostream>
    #include "ast/SyntaxTree.ih"

    int yylex(void);
    void yyerror(char const*);
    extern char* yytext;

    SyntaxTree* ast;
%}

%union {
    int                             INT;
    const char*                     STRING;
    class SyntaxTreeNode*           NODE;
}

%type <NODE> statements
%type <NODE> statement
%type <NODE> expression

%token <STRING> IDENTIFIER INVALID_IDENTIFIER
%token <INT> INTEGER
%token SEMICOLON PRINT_KEYWORD WHILE_KEYWORD LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE UNKNOWN

%precedence ASSIGNMENT
%left OP_PLUS OP_MINUS
%left OP_MUL OP_DIV
%precedence NEG

%start init

%%

init:
    statements                                  { ast = new SyntaxTree(new InitNode($1)); }

statements:
    statements statement                        { $$ = new StatementsNode($1, $2); }
    | %empty                                    { $$ = nullptr; }

statement:
    PRINT_KEYWORD expression SEMICOLON          { $$ = new PrintNode($2); }
    | WHILE_KEYWORD LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE
                                                { $$ = new WhileNode($3, $6); }
    | expression SEMICOLON                      { $$ = $1; }

expression:
      OP_MINUS expression %prec NEG             { $$ = new OpMinusNode(new IntegerNode(0), $2); }
    | IDENTIFIER ASSIGNMENT expression          { $$ = new AssignmentNode(new IdentifierNode($1), $3); }
    | expression OP_DIV expression              { $$ = new OpDivideNode($1, $3); }
    | expression OP_MUL expression              { $$ = new OpMultiplyNode($1, $3); }
    | expression OP_PLUS expression             { $$ = new OpPlusNode($1, $3); }
    | expression OP_MINUS expression            { $$ = new OpMinusNode($1, $3); }
    | LEFT_PAREN expression RIGHT_PAREN         { $$ = $2; }
    | IDENTIFIER                                { $$ = new IdentifierNode($1); }
    | INTEGER                                   { $$ = new IntegerNode($1); }

%%

void yyerror(char const* msg) {
    fprintf(stderr, "%s\n", msg);
}
