
%option noyywrap

%{

#include"parse.tab.h"

%}

%%
"+" { return TOKEN_ADD; }
"-" { return TOKEN_SUB; }
"*" { return TOKEN_MUL; }
"/" { return TOKEN_DIV; }
"(" { return TOKEN_OP; }
")" { return TOKEN_CP; }

[0-9]+ { yylval = atoi(yytext); return TOKEN_NUMBER; }

\n { return TOKEN_EOL; }

[ \t] { }
"//".* { }
. { printf("unknown char %c\n", *yytext); }

%%


