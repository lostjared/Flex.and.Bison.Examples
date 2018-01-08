#include"syntax-tree.hpp"

namespace ast {
    Symbol::Symbol(std::string n, std::string v, bool var) : name(n), value(v), variable(var) {
        
    }
    
    Symbol *createSymbol(std::string name, std::string value, bool var) {
        Symbol *s = new Symbol(name, value, var);
        if(!s) {
            std::cerr << "Error allocating memory..\n";
            return nullptr;
        }
        return s;
    }
}

void yyerror(const char *str, ...) {
    
}

