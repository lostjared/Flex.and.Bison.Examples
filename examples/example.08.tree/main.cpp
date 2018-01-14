#include"tree.hpp"
#include<cstdio>
#include<cstdarg>

extern int yyparse();
extern void yyrestart(FILE *fptr);

std::unordered_map<std::string, Symbol> symbols;
std::ostringstream code_stream;
std::ostringstream var_stream;
StringTree ast;

int main(int argc, char **argv) {
    if(argc == 1) {
    	std::cout << "$> ";
        yyparse();
    } else if(argc == 2) {
        FILE *fptr = fopen(argv[1], "r");
        if(!fptr) {
            std::cerr << "Error could not open file: " << argv[1] << "\n";
            exit(EXIT_FAILURE);
        }
        yyrestart(fptr);
        if(yyparse() == 0 && err_num == 0) {
            std::cout << "\nExiting, Success!...\n";
            fclose(fptr);
            exit(EXIT_SUCCESS);
        } else {
            std::cout << "Code has " << err_num << " error(s)...\n";
        	fclose(fptr);
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << "invalid arguments..\n";
    }
	return 0;
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

std::string trimQuotes(std::string value) {
    if(value[0] == '\"' && value.length()>=2) {
        std::string temp;
        temp = value.substr(1, value.length()-2);
        return temp;
    }
    return value;
}

