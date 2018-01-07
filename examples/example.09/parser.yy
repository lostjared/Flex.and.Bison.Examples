%{

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"table.hpp"
#include"syntax-tree.hpp"

extern int yylex();

%}

%union {
double d;
Symbol *s;
int fn;
}

%token NUMBER
%token NAME STR
%token EOL
%token FUNC
%token PRINT
%token STREAM


%start cmdlist

%%

cmdlist:
| EOL
;


%%
