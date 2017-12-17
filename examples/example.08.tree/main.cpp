#include"tree.hpp"


std::unordered_map<std::string, Symbol> symbols;

int main() {




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
