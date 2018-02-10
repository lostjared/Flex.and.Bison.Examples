/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#include"syntax-tree.hpp"

namespace ast {
    sym::SymbolTable<Symbol> sym_table;
    
    Symbol about_func(std::vector<Symbol> &vars) {
        std::cout << "created by Jared Bruni...\n";
        return Symbol(0);
    }
    
    void insert_functions() {
        Symbol sym;
        sym.name = "about";
        sym.type = Symbol_Type::FUNCTION;
        sym.function.setFunction("about", about_func);
        sym_table.insertTop("about", sym);
        
    }
    
    std::string escapeCharacters(std::string text) {
        std::string ec;
        for(unsigned int i = 0; i < text.length(); ++i) {
            if(text[i] == '\\') {
                ++i;
                switch(text[i]) {
                    case 'n':
                        ec += "\n";
                        break;
                    case 't':
                        ec += "\t";
                        break;
                    case 'r':
                        ec += "\r";
                        break;
                    case 'a':
                        ec += "\a";
                        break;
                    case 'b':
                        ec += "\b";
                        break;
                    case 'f':
                        ec += "\f";
                        break;
                    case 'v':
                        ec += "\v";
                        break;
                    case '\\':
                        ec += "\\";
                        break;
                    case '\'':
                        ec += "\'";
                        break;
                    case '\"':
                        ec += "\"";
                        break;
                }
            } else {
                ec += text[i];
            }
        }
        return ec;
    }
    
    std::string trimQuotes(std::string value) {
        if(value[0] == '\"' && value.length()>=2) {
            std::string temp;
            temp = value.substr(1, value.length()-2);
            return escapeCharacters(temp);
        }
        return escapeCharacters(value);
    }
    void procTree(AST *node) {
        try {
        	ast::Symbol s = eval(node);
#ifdef DEBUG_INFO
        	std::cout << "[ Value: " << s << "]\n";
#endif
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

