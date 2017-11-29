#include<iostream>
#include<algorithm>
#include<string>
#include "astheader.hpp"
#include "parser.tab.h"

extern void inputLoop(std::istream &in);
extern void inputLoop(int argc, char **argv);

int main(int argc, char **argv) {
    if(argc == 1)
        inputLoop(std::cin);
    else if(argc > 1) {
        inputLoop(argc, argv);
    }
    return 0;
}



