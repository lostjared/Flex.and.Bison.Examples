
%{

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"astheader.hpp"

%}

%union {
    AST *a;
    double d;
    Symbol *s;
    SymList *sl;
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
%type <a> exp stmt list explist
%type <sl> symlist
%start calclist
%token IF THEN ELSE WHILE DO LET
%%

calclist:
| calclist stmt EOL {
    double d = eval($2);
    if(cursor == 0) {
        std::cout << " = " << d << "\n";
        std::cout << "$> ";
    }
    freeAst($2);
}
| calclist LET NAME '(' symlist ')' '=' list EOL {
    doref($3, $5, $8);
    if(cursor == 0) {
    	std::cout << "Function Defined: " << $3->name << "\n$> ";
    }
}
| calclist error EOL {  std::cout << "\n"; if(cursor == 0) std::cout << "$> "; }
;

stmt: IF exp THEN list { $$ = createFlow('I', $2, $4, NULL); }
| IF exp THEN list ELSE list { $$ = createFlow('I', $2, $4, $6); }
| WHILE exp DO list  { $$ = createFlow('W', $2, $4, NULL); }
| exp
;

list: {$$ = NULL; }
| stmt ';' list {
    if($3 == NULL)
    $$ = $1;
    else
    $$ = createAst('L', $1, $3);
}
;

exp: exp CMP exp { $$ = createCmp($2, $1, $3); }
| exp '+' exp { $$ = createAst('+', $1, $3); }
| exp '-' exp { $$ = createAst('-', $1, $3); }
| exp '*' exp { $$ = createAst('*', $1, $3); }
| exp '/' exp { $$ = createAst('/', $1, $3); }
| '|' exp { $$ = createAst('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' exp %prec UMINUS { $$ = createAst('M', $2, NULL); }
| NUMBER { $$ = createNum($1); }
| NAME { $$ = createRef($1); }
| NAME '=' exp { $$ = createAssign($1, $3); }
| FUNC '(' explist ')' { $$ = createFunc($1, $3); }
| FUNC '(' ')' { $$ = createFuncNoArgs($1); }
| NAME '(' explist ')' { $$ = createCall($1, $3); }
;

explist: exp
| exp ',' explist { $$ = createAst('L',$1, $3); }
;
symlist: NAME { $$ = createSymList($1, NULL); }
| NAME ',' symlist { $$ = createSymList($1, $3); }
;

%%



