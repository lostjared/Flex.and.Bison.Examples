#include "mxl.hpp"

extern int yyparse();
extern void yyrestart(FILE *);

std::map<std::string, std::string> vars;

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Line %d: error  ", yylineno);
    vfprintf(stderr, src, ap);
    fprintf(stderr, "\n");
}

void readSource() {
    yyparse();
}

void readSource(std::string data) {
    FILE *fptr = fopen(data.c_str(), "r");
    yyrestart(fptr);
    readSource();
    fclose(fptr);
}

void echoTokens() {
    std::map<std::string, std::string>::iterator it;
    for(it = vars.begin(); it != vars.end(); ++it) {
        std::cout << "Variable [" << it->first << "] := " << it->second << "\n";
    }
}
