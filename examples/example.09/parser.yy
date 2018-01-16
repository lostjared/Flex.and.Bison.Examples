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
ast::AST *a;
ast::Symbol *s;
int fn;
}

%token <s> NAME STR NUMBER
%token <fn> FUNC
%token EOL
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%type <a> stmt expr

%token IF THEN ELSE WHILE DO LET PRINT STREAM
%start cmdlist
%%

cmdlist:
| cmdlist stmt EOL {
	ast::Symbol s = eval($2);
	std::cout << "Value: " << s.dvalue << ":" << s.value << "\n";
	freeAST($2);
}
| cmdlist stmt ';' {
	ast::Symbol s = eval($2);
	std::cout << "Value: " << s.dvalue << ":" << s.value << "\n";
	freeAST($2);
}
| cmdlist error EOL
| cmdlist EOL
;

stmt: expr
;

expr: expr '+' expr {
$$ = createNode('+', $1, $3);
}
| expr '-' expr {
$$ = createNode('-', $1, $3);
}
| expr '*' expr {
$$ = createNode('*', $1, $3);
}
| expr '/' expr {
$$ = createNode('/', $1, $3);
}
| '(' expr ')' { $$ = $2; }

| '-' expr %prec UMINUS {
$$ = createNode<NodeType>('M', $2, nullptr);
}

| NAME '=' expr {
$$ = createNode<NodeType>('=', $1, $3, nullptr);
}
| NUMBER {
$$ = createNodeValue<NodeType>('$', $1);
}
| NAME {
$$ = createNode<NodeType>('N', $1, nullptr, nullptr);
}
| STR {
$$ = createNode<NodeType>('S', $1, nullptr, nullptr);
}
;

%%
