
%option noyywrap

%{

#include<iostream>
#include<string>

int lines = 0;
enum { ID=260, DIGIT };


%}

%%

"\n" { lines++; }
[a-zA-z_]+[a-zA-z0-9_]* { std::cout << "Identifier: " << yytext << "\n"; if(std::string(yytext) == "quit") exit(0); return ID; }
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


