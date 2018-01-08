%{

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"table.hpp"
#include"syntax-tree.hpp"

extern int yylex();

%}

%union {
	ast::Symbol *s;
	double d;
}

%token <s> NAME STR
%token <d> NUMBER
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
