
%option noyywrap yylineno nodefault

%{
    #include<iostream>
    #include<map>
    #include "mxl.hpp"
    #include "parser.tab.hh"
    
%}



%%
[a-zA-z_][a-zA-Z0-9_]* { yylval.s = new Symbol(yytext); return ID; }
\"(([^\"]|\\\")*[^\\])?\" { yylval.s = new Symbol(yytext); return STR; }
[ \t] { }
"\n" { return EOL; }
"\\\n" { }
"=" { return yytext[0]; }
. {  }
%%


