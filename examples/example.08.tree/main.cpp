#include"tree.hpp"

extern int yyparse();

std::unordered_map<std::string, Symbol> symbols;
std::ostringstream code_stream;
std::ostringstream var_stream;
StringTree ast;

int main() {
    std::cout << "$> ";
    yyparse();
	return 0;
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Line %d: error ", yylineno);
    vfprintf(stderr, src, ap);
}
