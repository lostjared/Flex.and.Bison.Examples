%option noyywrap nodefault yylineno

%{
#include"syntax-tree.hpp"
#include "parser.tab.hh"
#include<iostream>
#include<cstdlib>

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
"exit" {
    ///yylval.fn = FN_EXIT;
    return FUNC; }
"print" { return PRINT; }
"<<" { return STREAM; }

[a-zA-Z]+[a-zA-Z0-9]* {
    yylval.s = ast::createSymbol(yytext, "", true);
    return NAME;
}
\"(([^\"]|\\\")*[^\\])?\" {
	yylval.s = ast::createSymbol("$const", yytext, false);
	return STR;
}
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? {
    yylval.d = atof(yytext);
    return NUMBER;    
}

\n { return EOL; }
\\\n { }
"//".*
[ \t] { }
. { yyerror("Mystery character: %c\n", *yytext); }


%%

