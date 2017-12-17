#include"tree.hpp"
#include<cstdio>

extern int yyparse();
extern void yyrestart(FILE *fptr);

std::unordered_map<std::string, Symbol> symbols;
std::ostringstream code_stream;
std::ostringstream var_stream;
StringTree ast;

int main(int argc, char **argv) {
    if(argc == 1) {
    	std::cout << "$> ";
    	yyparse();
    } else if(argc == 2) {
        FILE *fptr = fopen(argv[1], "r");
        yyrestart(fptr);
        yyparse();
        fclose(fptr);
        
    } else {
        std::cerr << "invalid arguments..\n";
    }
	return 0;
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Line %d: error ", yylineno);
    vfprintf(stderr, src, ap);
}
