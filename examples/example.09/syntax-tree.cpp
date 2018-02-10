/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#include"syntax-tree.hpp"
#include<cstdlib>
#include<ctime>

namespace ast {
    sym::SymbolTable<Symbol> sym_table;
    
    Symbol about_func(std::vector<Symbol> &vars) {
        std::cout << "created by Jared Bruni...\n";
        return Symbol(0);
    }
    
    Symbol rand_func(std::vector<Symbol> &vars) {
        
        if(vars.size()!=1) {
            throw SymbolException("Random function requires on argument...\n");
        }
        unsigned int max = static_cast<unsigned int>(vars[0].dvalue);
        
        return Symbol(rand()%max);
    }
    
    void addFunction(std::string name, FuncCall fn) {
        Symbol sym;
        sym.name = name;
        sym.type = Symbol_Type::FUNCTION;
        sym.function.setFunction(name, fn);
        sym_table.insertTop(name, sym);
    }
    
    void insert_functions() {
        srand(static_cast<unsigned int>(time(0)));
        addFunction("about", about_func);
        addFunction("random", rand_func);
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

