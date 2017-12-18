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
ast.root = $2;
double d = ast.eval();
std::cout << "Value is: " << d << "\n";
ast.release();
// proc node
std::cout << "$> ";
}
| calclist error EOL { std::cout << "$> "; }
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
| '-' exp %prec UMINUS { $$ = new StringNode("M", Var_type::MIN, $2, nullptr); }
| NAME {
$$ = new StringNode($1);
delete $1;
}
| NAME '=' exp {
$$ = new StringNode($1, $3);
delete $1;
}
;

%%

