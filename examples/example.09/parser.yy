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
	ast::Symbol *s = eval($2);
	std::cout << "Value: " << s->dvalue << "\n";
	if(s->free_memory == 1)
		delete s;
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

| NUMBER {
$$ = createNodeValue<NodeType>('$', $1);
}

;

%%
