%option noyywrap nodefault yylineno

%{
#include"tree.hpp"
#include "parser.tab.hh"
#include<iostream>
#include<cstdlib>

extern void yyerror(char *s, ...) ;

%}


EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")" |
"=" |
"," |
";" { return yytext[0]; }

[a-zA-Z][a-zA-Z0-9]* {  yylval.s = new Symbol(yytext, 0); return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
\\\n { }
"//".*
[ \t] { }
. { yyerror("Mystery character: %c\n", *yytext); }


%%

