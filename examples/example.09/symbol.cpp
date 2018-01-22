/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#include "symbol.hpp"

namespace ast {
    
    Symbol::Symbol() : dvalue(0), variable(false), free_memory(0), type(Symbol_Type::EMPTY) {}
    
    Symbol::Symbol(std::string n, std::string v) : name(n), value(v), dvalue(0), type(Symbol_Type::STRING), variable(true), free_memory(0) {}
    
    Symbol::Symbol(std::string n, double d) : name(n), dvalue(d), type(Symbol_Type::NUMERIC), variable(true), free_memory(0) {}
    
    Symbol::Symbol(double d) : name("const"), dvalue(d), type(Symbol_Type::CONSTANT_NUMERIC), variable(false), free_memory(0) {}
    
    Symbol::Symbol(std::string v) : name("const"), value(v), dvalue(0), type(Symbol_Type::CONSTANT_STRING), variable(false), free_memory(0) {}
    
    Symbol::Symbol(const Symbol &s): free_memory(0) {
        setSymbol(s);
    }
    
    Symbol &Symbol::operator=(const Symbol &s) {
        setSymbol(s);
        return *this;
    }
    
    Symbol::Function::Function(const Function &f) {
        setFunction(f);
    }
    
    Symbol::Function::Function(std::string n_name, FuncCall f) {
        setFunction(n_name, f);
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
    
    void Symbol::Function::setFunction(std::string n_name, FuncCall f) {
        name = n_name;
        func = f;
        args = nullptr;
        instruct = nullptr;
    }
    
    void Symbol::setSymbol(const Symbol &s) {
        dvalue = s.dvalue;
        variable = s.variable;
        name = s.name;
        type = s.type;
        value = s.value;
        function = s.function;
        free_memory = s.free_memory;
    }
    
    Symbol *createSymbol(std::string name, std::string value) {
        Symbol *s = new Symbol(name, value);
        if(!s) {
            std::ostringstream stream;
            stream << "Error allocating: " << name << "\n";
            throw SymbolException(stream.str());
            return nullptr;
        }
        return s;
    }
    
    Symbol *createEmptySymbol(std::string name) {
        Symbol *s = new Symbol();
        if(!s) {
            std::ostringstream stream;
            stream << "Error allocating: " << name << "\n";
            throw SymbolException(stream.str());
            return nullptr;
        }
        s->name = name;
        s->type = Symbol_Type::EMPTY;
        s->variable = true;
        s->free_memory = 0;
        s->dvalue = 0;
        return s;
    }
    
    Symbol *createSymbol(std::string value) {
        Symbol *s = new Symbol(value);
        if(!s) {
            std::ostringstream stream;
            stream << "Error allocating value: " << value << "\n";
            throw SymbolException(stream.str());
            return nullptr;
        }
        return s;
    }
    
    Symbol *createSymbol(std::string n, double v) {
        Symbol *s = new Symbol(n, v);
        if(!s) {
            std::ostringstream stream;
            stream << "Error allocating: " << n << "\n";
            throw SymbolException(stream.str());
            return nullptr;
        }
        return s;
    }
    
    Symbol *createSymbol(double d) {
        Symbol *s = new Symbol(d);
        if(!s) {
            std::ostringstream stream;
            stream << "Error allocating value: " << d << "\n";
            throw SymbolException(stream.str());
            return nullptr;
        }
        return s;
    }
    
    Symbol *createFunction(std::string name, AST_Node<NodeType> *f) {
        Symbol *s = new Symbol();
        if(!s) {
            std::ostringstream stream;
            stream << "Error allocating function: " << name << "\n";
            throw SymbolException(stream.str());
            return nullptr;
        }
        s->function.name = name;
        s->function.instruct = f;
        s->type = Symbol_Type::FUNCTION;
        return s;
    }
}

std::ostream &operator<<(std::ostream &out, const ast::Symbol &s) {    
    out << "Symbol [" << s.name << ":" << s.value << ":" << s.dvalue << " -> " << s.type << "] ";
    if(s.function.func != nullptr)
        out << " - Function [" << s.function.name << "]";
    return out;
}

std::ostream &operator<<(std::ostream &out, const ast::Symbol_Type &t) {
    switch(t) {
        case ast::Symbol_Type::EMPTY:
            out << "Empty";
            break;
        case ast::Symbol_Type::STRING:
            out << "String";
            break;
        case ast::Symbol_Type::NUMERIC:
            out << "Numeric";
            break;
        case ast::Symbol_Type::CONSTANT_STRING:
            out << "Constant String";
            break;
        case ast::Symbol_Type::CONSTANT_NUMERIC:
            out << "Constant Numeric";
            break;
        case ast::Symbol_Type::FUNCTION:
            out << "Function";
            break;
    }
    return out;
}

