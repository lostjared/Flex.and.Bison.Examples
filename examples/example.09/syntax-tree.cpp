#include"syntax-tree.hpp"

namespace ast {
    Symbol::Symbol(std::string n, std::string v) : name(n), value(v) {
        
    }
}

void yyerror(const char *str, ...) {
    
}

