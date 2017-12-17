#include"tree.hpp"

extern int yyparse();

std::unordered_map<std::string, Symbol> symbols;
StringTree ast;

int main() {
    yyparse();
	return 0;
}

void add_token(std::string name, double value) {
    symbols[name].name = name;
    symbols[name].value = value;
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Line %d: error ", yylineno);
    vfprintf(stderr, src, ap);
}
