%option noyywrap
%{
#include "../generated/grammar.tab.h"
%}

IDENTIFIER              [_a-zA-Z][_a-zA-Z0-9]*
INTEGER                 [0-9]+
WHITESPACE              [ \r\t\v\f]
LINEFEED                \n
PRINT_KEYWORD           print

%%

{PRINT_KEYWORD}                 return PRINT_KEYWORD;
{IDENTIFIER}                    { yylval.STRING = yytext; return IDENTIFIER; }
{INTEGER}                       { yylval.INT = atoi(yytext); return INTEGER; }
{WHITESPACE}                    /* Empty */
{LINEFEED}                      ++yylineno;
";"                             return SEMICOLON;
"/"                             return OP_DIV;
"*"                             return OP_MUL;
"+"                             return OP_PLUS;
"-"                             return OP_MINUS;
"("                             return LEFT_PAREN;
")"                             return RIGHT_PAREN;
.                               { printf("unexpected character: %s", yytext); }

%%
