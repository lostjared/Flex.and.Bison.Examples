#include"syntax-tree.hpp"

namespace ast {
    
    Symbol::Symbol(std::string n, std::string v) : name(n), value(v), dvalue(0), type(Symbol_Type::STRING), variable(true) {}
    
    Symbol::Symbol(std::string n, double d) : name(n), dvalue(d), type(Symbol_Type::NUMERIC), variable(true) {}
    
    Symbol::Symbol(double d) : name("const"), dvalue(d), type(Symbol_Type::CONSTANT_NUMERIC), variable(false) {}
    
    Symbol::Symbol(std::string v) : name("const"), value(v), dvalue(0), type(Symbol_Type::CONSTANT_STRING), variable(false) {}

    
    Symbol *createSymbol(std::string name, std::string value) {
        Symbol *s = new Symbol(name, value);
        if(!s) {
            std::cerr << "Error allocating memory..\n";
            return nullptr;
        }
        return s;
    }
    
    Symbol *createSymbol(std::string value) {
        Symbol *s = new Symbol(value);
        if(!s) {
            std::cerr << "Error allocating memory..\n";
            return nullptr;
        }
        return s;
    }
    
    Symbol *createSymbol(std::string n, double v) {
        Symbol *s = new Symbol(n, v);
        if(!s) {
            std::cerr << "Error allocating memory..\n";
            return nullptr;
        }
        return s;
    }
    
    Symbol *createSymbol(double d) {
        Symbol *s = new Symbol(d);
        if(!s) {
            std::cerr << "Error allocating memory..\n";
            return nullptr;
        }
        return s;
    }
    
    
}

void yyerror(const char *str, ...) {
    
}

