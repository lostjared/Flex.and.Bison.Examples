#include<iostream>
#include "astheader.hpp"

extern int yyparse();

int main(int argc, char **argv) {
   	std::cout << "$> ";
    yyparse();
    return 0;
}
