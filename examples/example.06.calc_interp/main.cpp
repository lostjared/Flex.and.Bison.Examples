#include<iostream>
#include "astheader.hpp"

extern int yyparse();
int arg_count = 0;
int main(int argc, char **argv) {
    arg_count = argc;
    if(argc == 1) {
    	std::cout << "$> ";
    }
    yyparse();
    return 0;
}
