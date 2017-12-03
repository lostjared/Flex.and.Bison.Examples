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
%type <l> val_start;
%token EOL
%token ARROW;
%start main_list
%%

main_list:
| main_list val_start EOL
| main_list val_list EOL
| main_list error EOL
| main_list EOL
;



val_list: ID '=' ID { vars[current_name][$1->name] = $3->name;
    delete $1;
    delete $3;
}
| ID '=' STR { vars[current_name][$1->name] = mxl::trimQuotes($3->name);
    delete $1;
    delete $3;
}
;
val_start: ID ARROW {
	current_name = $1->name;
	delete $1;
}

%%
