%{

#include<iostream>
#include<string>
#include<map>
#include"mxl.hpp"

extern int yylex();

%}

%union {
    Symbol *s;
    List *l;
}


%token <s> ID STR
%type <l> val_list
%token EOL
%start main_list
%%

main_list:
| main_list val_list EOL
| main_list error EOL
| main_list EOL
;

val_list: ID '=' ID { vars[$1->name] = $3->name;
    delete $1;
    delete $3;
}
| ID '=' STR { vars[$1->name] = $3->name;
    delete $1;
    delete $3;
}
;

%%
