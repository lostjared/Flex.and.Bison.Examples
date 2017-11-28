
%option noyywrap nodefault yylineno

%{
    #include "astheader.hpp"
    #include "parser.tab.h"
    #include<cstdlib>
    #include<cstdio>
    
    extern void releaseBuffer();
    
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

">"  { yylval.fn = 1; return CMP; }
"<"  { yylval.fn = 2; return CMP; }
"<>"  { yylval.fn = 3; return CMP; }
"=="  { yylval.fn = 4; return CMP; }
">="  { yylval.fn = 5; return CMP; }
"<="  { yylval.fn = 6; return CMP; }

"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"while" { return WHILE; }
"do" { return DO; }
"let" { return LET; }

"sqrt" {yylval.fn = FN_SQRT; return FUNC; }
"exp"  {yylval.fn = FN_EXP; return FUNC; }
"log"  {yylval.fn = FN_LOG; return FUNC; }
"print" { yylval.fn = FN_PRINT; return FUNC; }
"exit" { yylval.fn = FN_EXIT; return FUNC; }

[a-zA-z][a-zA-Z0-9]* { yylval.s = getSymbol(yytext); return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
\\\n { std::cout << "$> "; }
"//".*
[ \t] { }
. { yyerror("Mystery character: %c\n", *yytext); }

%%

void releaseBuffer() {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}


