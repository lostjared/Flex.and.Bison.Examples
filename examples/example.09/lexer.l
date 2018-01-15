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


"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"while" { return WHILE; }
"do" { return DO; }
"let" { return LET; }

[a-zA-Z]+[a-zA-Z0-9]* {
    yylval.s = ast::createSymbol(yytext, "");
    return NAME;
}
\"(([^\"]|\\\")*[^\\])?\" {
	yylval.s = ast::createSymbol(std::string(yytext));
	return STR;
}
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? {
    yylval.s = ast::createSymbol(atof(yytext));
    return NUMBER;    
}

\n { return EOL; }
\\\n { }
"//".*
[ \t] { }
. { yyerror("Mystery character: %c\n", *yytext); }


%%

