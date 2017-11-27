#include<iostream>
#include "astheader.hpp"

extern int yyparse();

int main() {
    std::cout << "$> ";
    yyparse();
    return 0;
}
