%option noyywrap
%{
#include "../generated/grammar.tab.h"
%}

IDENTIFIER              [_a-zA-Z][_a-zA-Z0-9]*
INTEGER                 [0-9]+
WHITESPACE              [ \r\t\v\f]
LINEFEED                \n
PRINT_KEYWORD           print
WHILE_KEYWORD           while
LINE_COMMENT            \/\/.*

%%

{WHITESPACE}                    /* Empty */
{LINE_COMMENT}                  /* Empty */
{PRINT_KEYWORD}                 return PRINT_KEYWORD;
{WHILE_KEYWORD}                 return WHILE_KEYWORD;
{IDENTIFIER}                    { yylval.STRING = strdup(yytext); return IDENTIFIER; }
{INTEGER}                       { yylval.INT = atoi(yytext); return INTEGER; }
{LINEFEED}                      ++yylineno;
";"                             return SEMICOLON;
"/"                             return OP_DIV;
"*"                             return OP_MUL;
"+"                             return OP_PLUS;
"-"                             return OP_MINUS;
"("                             return LEFT_PAREN;
")"                             return RIGHT_PAREN;
"{"                             return LEFT_BRACE;
"}"                             return RIGHT_BRACE;
"="                             return ASSIGNMENT;
.                               { printf("unexpected character: %s", yytext); }

%%
