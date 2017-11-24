
%option noyywrap

%{

#include<iostream>
int lines = 0;

enum { ID=260, DIGIT };


%}

%%

"\n" { lines++; }
[a-zA-z]+[a-zA-z0-9]* { std::cout << "Identifier: " << yytext << "\n"; return ID; }
[0-9]+ { std::cout << "Digits: " << yytext << "\n"; return DIGIT; }
[ \t]* { }
. { }

%%

int main() {

	int token_type = 0;
	while((token_type = yylex()) != 0) {
		std::cout << "Token type: " << token_type << "\n";
	}

	return 0;
}


