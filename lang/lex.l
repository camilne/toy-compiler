%option noyywrap
%{
#include "grammar.tab.h"
%}

IDENTIFIER              [_[:alpha:]][_[:alnum:]]*
INTEGER                 [[:digit:]]+
INVALID_IDENTIFIER      [[:digit:]]+[_[:alnum:]]+
WHITESPACE              [ \r\t\v\f]
LINEFEED                \n
PRINT_KEYWORD           print
WHILE_KEYWORD           while
LINE_COMMENT            "//".*
BLOCK_COMMENT           "/*"[^*]*[*]+([^*/][^*]*[*]+)*[/]

%%

{WHITESPACE}                    /* Empty */
{LINE_COMMENT}                  /* Empty */
{BLOCK_COMMENT}                 /* Empty */
{PRINT_KEYWORD}                 return PRINT_KEYWORD;
{WHILE_KEYWORD}                 return WHILE_KEYWORD;
{INTEGER}                       { yylval.INT = atoi(yytext); return INTEGER; }
{INVALID_IDENTIFIER}            { yylval.STRING = strdup(yytext); return INVALID_IDENTIFIER; }
{IDENTIFIER}                    { yylval.STRING = strdup(yytext); return IDENTIFIER; }
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
.                               { yylval.STRING = strdup(yytext); return UNKNOWN; }

%%
