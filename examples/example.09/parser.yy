%{

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"table.hpp"
#include"syntax-tree.hpp"

extern int yylex();

using namespace ast;


%}

%union {
ast::AST_Node<ast::NodeType> *a;
double d;
ast::Symbol *s;
}

%token <d> NUMBER
%token <s> NAME
%token <s> STR
%token <fn> FUNC
%token EOL
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%type <a> stmt
%token IF THEN ELSE WHILE DO LET PRINT STREAM
%start cmdlist
%%

cmdlist:
| cmdlist stmt EOL
| cmdlist error EOL
| cmdlist EOL
;

stmt: IF { }
;


%%
