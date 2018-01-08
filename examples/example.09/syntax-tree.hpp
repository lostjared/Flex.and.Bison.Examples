#ifndef __SYNTAX_TREE 
#define __SYNTAX_TREE

#include"table.hpp"


namespace ast {
    
    enum { FN_EXIT, FN_PRINT, FN_SQRT };
    
    class Symbol {
    public:
        Symbol(std::string name, std::string value);
        bool variable;
        
    private:
        std::string name,value;
    };
    
}

extern void yyerror(const char *str, ...);


#endif

