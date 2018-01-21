/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#include"syntax-tree.hpp"

namespace ast {
    sym::SymbolTable<Symbol> sym_table;
    
    std::string trimQuotes(std::string value) {
        if(value[0] == '\"' && value.length()>=2) {
            std::string temp;
            temp = value.substr(1, value.length()-2);
            return temp;
        }
        return value;
    }
    void procTree(AST *node) {
        try {
        	ast::Symbol s = eval(node);
        	std::cout << "Value: " << s << "\n";
        	freeAST(node);
        }
        catch(ast::SymbolException &se) {
            std::cerr << "Error: " << se.get() << "\n";
        } catch(ast::DivideByZero) {
            std::cerr << "Error: divide by Zero...\n";
        }
    }
}


int err_num = 0;

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Error on Line %d: ", yylineno);
    vfprintf(stderr, src, ap);
    fprintf(stderr, "\n");
    ++err_num;
}

