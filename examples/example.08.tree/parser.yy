%{

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"tree.hpp"

extern int yylex();

%}


%union {
StringNode *a;
double d;
Symbol *s;
int fn;
}

%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token EOL
%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%type <a> exp stmt
%start calclist
%%


calclist:
| calclist stmt EOL {

// proc node
std::cout << "$> ";
}
| calclist error EOL { }
| calclist EOL
;

stmt: exp
;

exp: exp '+' exp {
$$ = new StringNode("+", Var_type::PLUS, $1, $3);
}
| exp '-' exp {
$$ = new StringNode("-", Var_type::MINUS, $1, $3);
}
| exp '*' exp {
$$ = new StringNode("*", Var_type::MULT, $1, $3);
}
| exp '/' exp {
$$ = new StringNode("/", Var_type::DIV, $1, $3);
}
| '(' exp ')' { $$ = $2; }
| NUMBER {
$$ = new StringNode($1);
}
| NAME {
$$ = new StringNode($1);

}
;

%%

