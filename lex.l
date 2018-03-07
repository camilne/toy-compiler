%option noyywrap
%{
#include "grammar.tab.h"
%}

IDENTIFIER              [_a-zA-Z][_a-zA-Z0-9]*
INTEGER                 [0-9]+
WHITESPACE              [ \r\t\v\f]
LINEFEED                \n

%%

{IDENTIFIER}                    { yylval.STRING = yytext; return IDENTIFIER; }
{INTEGER}                       { yylval.INT = atoi(yytext); return INTEGER; }
{WHITESPACE}                    /* Empty */
{LINEFEED}                      ++yylineno;
";"                             return SEMICOLON;
"+"                             return OP_PLUS;
"-"                             return OP_MINUS;
.                               { printf("unexpected character: %s", yytext); }

%%
