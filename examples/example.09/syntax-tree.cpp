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
            std::cerr << "Runtime Error: " << se.get() << "\n";
            exit(EXIT_FAILURE);
        } catch(ast::DivideByZero) {
            std::cerr << "Runtime Error: divide by Zero Exception...\n";
            exit(EXIT_FAILURE);
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

