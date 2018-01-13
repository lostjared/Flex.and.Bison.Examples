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
	ast::AST_Node<ast::NodeType> *a;
}

%token <s> NAME STR NUMBER
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
