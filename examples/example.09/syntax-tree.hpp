#ifndef __SYNTAX_TREE 
#define __SYNTAX_TREE

#include"table.hpp"


namespace ast {
    
    enum { FN_EXIT, FN_PRINT, FN_SQRT };
    
    enum class Symbol_Type { STRING, CONSTANT, NUMERIC };
    
    class Symbol {
    public:
        Symbol(std::string name, std::string value, bool variable);
        Symbol(std::string name, double d);
        Symbol(double d);
        Symbol(std::string value);
        
        std::string name,value;
        double dvalue;
        Symbol_Type type;
        bool variable;
    };
    
    Symbol *createSymbol(std::string name, std::string value, bool var);
    Symbol *createSymbol(std::string value);
    Symbol *createSymbol(double d);
    Symbol *createSymbol(std::string n, double v);
    
    class AST_Node {
    public:
        Symbol *sym;
        AST_Node *left, *right;
    };
    
}

extern void yyerror(const char *str, ...);


#endif

