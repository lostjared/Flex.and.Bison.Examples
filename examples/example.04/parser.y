
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

%token <d> NUMBER
%token EOL

%type <a> exp factor term

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

exp: factor
| exp '+' factor { $$ = createAst('+', $1, $3); }
| exp '-' factor { $$ = createAst('-', $1, $3); }
;

factor: term
| factor '*' term { $$ = createAst('*', $1, $3); }
| factor '/' term { $$ = createAst('/', $1, $3); }

term: NUMBER { $$ = createNum($1); }
| '|' term { $$ = createAst('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' term { $$ = createAst('M', $2, NULL); }
;
%%



