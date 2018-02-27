/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#include"syntax-tree.hpp"
#include<cstdlib>
#include<ctime>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<unistd.h>

namespace ast {
    
    int System(const std::string &command) {
        sigset_t bmask, omask;
        struct sigaction sa_ignore, sa_oquit, sa_origint, sa_default;
        pid_t id;
        int status, serrno;
        
        if(command == "") return System(":") == 0;
        
        sigemptyset(&bmask);
        sigaddset(&bmask, SIGCHLD);
        sigprocmask(SIG_BLOCK, &bmask, &omask);
        sa_ignore.sa_handler = SIG_IGN;
        sa_ignore.sa_flags = 0;
        sigemptyset(&sa_ignore.sa_mask);
        sigaction(SIGINT, &sa_ignore, &sa_origint);
        sigaction(SIGQUIT, &sa_ignore, &sa_oquit);
        
        switch((id = fork())) {
            case -1:
                status = -1;
                break;
            case 0:
                sa_default.sa_handler = SIG_DFL;
                sa_default.sa_flags = 0;
                sigemptyset(&sa_default.sa_mask);
                if(sa_origint.sa_handler != SIG_IGN)
                    sigaction(SIGINT, &sa_default, NULL);
                if(sa_oquit.sa_handler != SIG_IGN)
                    sigaction(SIGQUIT, &sa_default, NULL);
                
                execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
                _exit(127);
                break;
            default:
                while(waitpid(id, &status, 0) == -1) {
                    if(errno != EINTR) {
                        status = -1;
                        break;
                    }
                }
                break;
        }
        serrno = errno;
        sigprocmask(SIG_SETMASK, &omask, NULL);
        sigaction(SIGINT, &sa_origint, NULL);
        sigaction(SIGQUIT, &sa_oquit, NULL);
        errno = serrno;
        return status;
    }
    
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
    
    Symbol shell_func(std::vector<Symbol> &vars) {
        if(vars.size()!=1)
            throw SymbolException("Requires one string argument with bash");
        
        if(vars[0].type != Symbol_Type::CONSTANT_STRING && vars[0].type != Symbol_Type::STRING)
            throw SymbolException("Requires string argument with code");
        
        std::string param = vars[0].value;
        return Symbol(System(param));
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
        addFunction("sh", shell_func);
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

