
%option noyywrap nodefault yylineno

%{
    #include "astheader.hpp"
    #include "parser.tab.h"
    #include<cstdlib>
    #include<cstdio>
    
    extern void inputLoop(std::istream &in);
    extern void inputLoop(int argc, char **argv);
    extern int yyparse();
%}

EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")" |
"=" |
"," |
";" { return yytext[0]; }

">"  { yylval.fn = 1; return CMP; }
"<"  { yylval.fn = 2; return CMP; }
"<>"  { yylval.fn = 3; return CMP; }
"=="  { yylval.fn = 4; return CMP; }
">="  { yylval.fn = 5; return CMP; }
"<="  { yylval.fn = 6; return CMP; }

"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"while" { return WHILE; }
"do" { return DO; }
"let" { return LET; }

"sqrt" {yylval.fn = FN_SQRT; return FUNC; }
"exp"  {yylval.fn = FN_EXP; return FUNC; }
"log"  {yylval.fn = FN_LOG; return FUNC; }
"print" { yylval.fn = FN_PRINT; return FUNC; }
"exit" { yylval.fn = FN_EXIT; return FUNC; }
"input" { yylval.fn = FN_INPUT; return FUNC; }

[a-zA-Z][a-zA-Z0-9]* { yylval.s = getSymbol(yytext); return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
\\\n { if(cursor == 0) std::cout << "$> "; }
"//".*
[ \t] { }
. { yyerror("Mystery character: %c\n", *yytext); }

%%

void inputLoop(std::istream &in) {
    std::cout << "$> ";
    while(!in.eof()) {
        std::string value;
        std::getline(in, value);
        YY_BUFFER_STATE buffer;
        if(in && value.length() > 0) {
            value += "\n\0";
            buffer = yy_scan_string((char*)value.c_str());
            yyparse();
            yy_delete_buffer(YY_CURRENT_BUFFER);
        } else {
            std::cout << "$> ";
        }
    }
}

void inputLoop(int argc, char **argv) {
    for(unsigned int i = 1; i < argc; i++) {
        FILE *fptr;
        fptr = fopen(argv[i], "r");
        yyrestart(fptr);
        yyparse();
    }
}

