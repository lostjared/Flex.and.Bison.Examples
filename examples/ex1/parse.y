%{

#include<stdio.h>

%}

%token TOKEN_NUMBER
%token TOKEN_ADD TOKEN_SUB TOKEN_MUL TOKEN_DIV TOKEN_ABS
%token TOKEN_EOL
%token TOKEN_OP
%token TOKEN_CP

%%

calclist:
| calclist exp TOKEN_EOL { printf(" Result = %d\n", $2); }
;

exp: factor
| exp TOKEN_ADD factor { $$ = $1 + $3; }
| exp TOKEN_SUB factor { $$ = $1 - $3; }
;

factor: term
| factor TOKEN_MUL term { $$ = $1 * $3; }
| factor TOKEN_DIV term  { $$ = $1 / $3; }
;

term: TOKEN_NUMBER
| TOKEN_OP exp TOKEN_CP { $$ = $2; }
;

%%

int main() {
	yyparse();
	return 0;
}

int yyerror(char *s) {
	printf("Error: %s\n", s);
	return 0;
}

