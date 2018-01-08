#include"syntax-tree.hpp"

namespace ast {
    Symbol::Symbol(std::string n, std::string v) : name(n), value(v) {
        
    }
    
    Symbol *createSymbol(std::string name, std::string value, bool var) {
        Symbol *s = new Symbol(name, value);
        if(!s) {
            std::cerr << "Error allocating memory..\n";
            return nullptr;
        }
        s->variable = var;
        return s;
    }
}

void yyerror(const char *str, ...) {
    
}

