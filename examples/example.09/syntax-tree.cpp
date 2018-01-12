#include"syntax-tree.hpp"

namespace ast {
    
    Symbol::Symbol() : dvalue(0), variable(false) {}
    Symbol::Symbol(std::string n, std::string v) : name(n), value(v), dvalue(0), type(Symbol_Type::STRING), variable(true) {}
    
    Symbol::Symbol(std::string n, double d) : name(n), dvalue(d), type(Symbol_Type::NUMERIC), variable(true) {}
    
    Symbol::Symbol(double d) : name("const"), dvalue(d), type(Symbol_Type::CONSTANT_NUMERIC), variable(false) {}
    
    Symbol::Symbol(std::string v) : name("const"), value(v), dvalue(0), type(Symbol_Type::CONSTANT_STRING), variable(false) {}

    Symbol::Symbol(const Symbol &s) {
        setSymbol(s);
    }
    
    Symbol &Symbol::operator=(const Symbol &s) {
        setSymbol(s);
        return *this;
    }
    
    Symbol::Function::Function(const Function &f) {
        setFunction(f);
        
    }
    
    Symbol::Function &Symbol::Function::operator=(const Symbol::Function &f) {
        setFunction(f);
        return *this;
    }
    
    void Symbol::Function::setFunction(const Symbol::Function &f) {
        func = f.func;
        name = f.name;
        args = f.args;
        instruct = f.instruct;
    }
    
    void Symbol::setSymbol(const Symbol &s) {
        dvalue = s.dvalue;
        variable = s.variable;
        name = s.name;
        type = s.type;
        value = s.value;
        function = s.function;
    }
    
    void Symbol::Function::setFunction(std::string n_name, FuncCall f) {
        name = n_name;
        func = f;
    }
    
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
    
    Symbol *createFunction(std::string name, AST_Node<NodeType> *f) {
        Symbol *s = new Symbol();
        if(!s) {
            std::cerr << "Error allocating function...\n";
            return nullptr;
        }
        s->function.name = name;
        s->function.instruct = f;
        s->type = Symbol_Type::FUNCTION;
        return s;
    }
    
}

void yyerror(const char *str, ...) {
    
}

