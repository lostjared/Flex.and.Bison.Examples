%option noyywrap nodefault yylineno

%{
/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
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
"\$" |
";" { return yytext[0]; }
"exit" {
    yylval.s = ast::createFunction("exit", nullptr);
    yylval.s->function.fn = ast::FN_EXIT;
    return FUNC;
}

"println" {
    yylval.s = ast::createFunction("println", nullptr);
    yylval.s->function.fn = ast::FN_PRINTLN;
    return FUNC;
}
"print" {
    yylval.s = ast::createFunction("print", nullptr);
    yylval.s->function.fn = ast::FN_PRINT;
    return FUNC;
}
"input_number" {
    yylval.s = ast::createFunction("input_number", nullptr);
    yylval.s->function.fn = ast::FN_INPUT_NUMBER;
    return FUNC;
}
"input_string" {
    yylval.s = ast::createFunction("input_string", nullptr);
    yylval.s->function.fn = ast::FN_INPUT_STRING;
    return FUNC;
}
"sqrt" {
    yylval.s = ast::createFunction("sqrt", nullptr);
    yylval.s->function.fn = ast::FN_SQRT;
    return FUNC;
}
"sin" {
    yylval.s = ast::createFunction("sin", nullptr);
    yylval.s->function.fn = ast::FN_SIN;
    return FUNC;
}
"cos" {
    yylval.s = ast::createFunction("cos", nullptr);
    yylval.s->function.fn = ast::FN_COS;
    return FUNC;
}
"tan" {
    yylval.s = ast::createFunction("tan", nullptr);
    yylval.s->function.fn = ast::FN_TAN;
    return FUNC;
}
"<<" { return STREAM; }


"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"while" { return WHILE; }
"do" { return DO; }
"let" { return LET; }

[a-zA-Z_]+[a-zA-Z0-9_]* {
    yylval.s = ast::createEmptySymbol(yytext);
    return NAME;
}
\"(([^\"]|\\\")*[^\\])?\" {
	yylval.s = ast::createSymbol(std::string(yytext));
	yylval.s->value = ast::trimQuotes(yylval.s->value);
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

