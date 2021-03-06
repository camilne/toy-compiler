%option noyywrap
%{
#include "grammar.tab.h"
%}

IDENTIFIER              [_[:alpha:]][_[:alnum:]]*
INTEGER                 [[:digit:]]+
INVALID_IDENTIFIER      {INTEGER}{IDENTIFIER}
WHITESPACE              [ \r\t\v\f]
LINEFEED                \n
PRINT_KEYWORD           print
WHILE_KEYWORD           while
IF_KEYWORD              if
ELSE_KEYWORD            else
LINE_COMMENT            "//".*
BLOCK_COMMENT           "/*"[^*]*[*]+([^*/][^*]*[*]+)*[/]

%%

{WHITESPACE}                    /* Empty */
{LINE_COMMENT}                  /* Empty */
{BLOCK_COMMENT}                 /* Empty */
{PRINT_KEYWORD}                 return PRINT_KEYWORD;
{WHILE_KEYWORD}                 return WHILE_KEYWORD;
{IF_KEYWORD}                    return IF_KEYWORD;
{ELSE_KEYWORD}                  return ELSE_KEYWORD;
{INTEGER}                       { yylval.INT = atoi(yytext); return INTEGER; }
{INVALID_IDENTIFIER}            { yylval.STRING = strdup(yytext); return INVALID_IDENTIFIER; }
{IDENTIFIER}                    { yylval.STRING = strdup(yytext); return IDENTIFIER; }
{LINEFEED}                      ++yylineno;
";"                             return SEMICOLON;
"/"                             return OP_DIV;
"-"                             return OP_MINUS;
"*"                             return OP_MUL;
"+"                             return OP_PLUS;
"("                             return LEFT_PAREN;
")"                             return RIGHT_PAREN;
"{"                             return LEFT_BRACE;
"}"                             return RIGHT_BRACE;
"<"                             return LESS_THAN;
"<="                            return LESS_THAN_EQUAL;
">"                             return GREATER_THAN;
">="                            return GREATER_THAN_EQUAL;
"!="                            return NOT_EQUALITY;
"=="                            return EQUALITY;
"="                             return ASSIGNMENT;
.                               { yylval.STRING = strdup(yytext); return UNKNOWN; }

%%
