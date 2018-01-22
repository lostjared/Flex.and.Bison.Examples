/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#ifndef __SYMBOL__H__
#define __SYMBOL__H__

#include<iostream>
#include<string>

namespace ast {
    
    class NodeType;
    
    template<typename T>
    class AST_Node;
    
    class SymbolException {
    public:
        std::string value;
        SymbolException(std::string s) : value(s) {}
        std::string get() const { return value; }
    };
    
    enum class Symbol_Type { EMPTY, STRING, NUMERIC, CONSTANT_STRING, CONSTANT_NUMERIC, FUNCTION };
    
    class SymList {
    public:
        AST_Node<NodeType> *arg;
        SymList *next;
        
    };
    
    class Symbol {
    public:
        Symbol(std::string name, std::string value);
        Symbol(std::string name, double d);
        Symbol(double d);
        Symbol(std::string value);
        Symbol(const Symbol &s);
        Symbol();
        
        std::string name,value;
        double dvalue;
        Symbol_Type type;
        bool variable;
        int free_memory;
        
        class Function {
        public:
            using FuncCall = void (*)(SymList *);
            Function() : func(nullptr), args(nullptr), instruct(nullptr) {}
            Function(const Function &f);
            Function(std::string n_name, FuncCall f);
            Function &operator=(const Function &f);
            std::string name;
            FuncCall func;
            SymList *args;
            AST_Node<NodeType> *instruct;
            void setFunction(const Function &f);
            void setFunction(std::string n_name, FuncCall f);
        };
        Function function;
        Symbol &operator=(const Symbol &s);
        void setSymbol(const Symbol &s);
    };
    
    Symbol *createSymbol(std::string name, std::string value);
    Symbol *createEmptySymbol(std::string name);
    Symbol *createSymbol(std::string value);
    Symbol *createSymbol(double d);
    Symbol *createSymbol(std::string n, double v);
    Symbol *createFunction(std::string name, AST_Node<NodeType> *f);
    
}

std::ostream &operator<<(std::ostream &out, const ast::Symbol &s);
std::ostream &operator<<(std::ostream &out, const ast::Symbol_Type &t);

#endif
