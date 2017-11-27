
%{

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"astheader.hpp"
    
%}

%union {
    AST *a;
    double d;
}

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%token <d> NUMBER
%token EOL
%type <a> exp

%%

calclist:
| calclist exp EOL {
    std::cout << " = " << eval($2) << "\n";
    freeAst($2);
    std::cout << "$> ";
}
| calclist EOL {
    std::cout << "$> ";
}
;
exp: exp '+' exp { $$ = createAst('+', $1, $3); }
| exp '-' exp { $$ = createAst('-', $1, $3); }
| exp '*' exp { $$ = createAst('*', $1, $3); }
| exp '/' exp { $$ = createAst('/', $1, $3); }
| '|' exp { $$ = createAst('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' exp %prec UMINUS { $$ = createAst('M', NULL, $2); }
| NUMBER { $$ = createNum($1); }
;

%%



