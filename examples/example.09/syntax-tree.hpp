#ifndef __SYNTAX_TREE 
#define __SYNTAX_TREE

#include"table.hpp"


namespace ast {
    
    enum { FN_EXIT, FN_PRINT, FN_SQRT };
    
    class Symbol {
    public:
        Symbol(std::string name, std::string value, bool variable);
        
        std::string name,value;
        bool variable;
    };
    
    Symbol *createSymbol(std::string name, std::string value, bool var);
    
}

extern void yyerror(const char *str, ...);


#endif

