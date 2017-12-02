#include<iostream>
#include<algorithm>
#include<string>
#include "astheader.hpp"
#include "parser.tab.hh"

extern void inputLoop(std::istream &in);
extern void inputLoop(int argc, char **argv);

unsigned int cursor;

int main(int argc, char **argv) {
    if(argc == 1) {
        cursor = 0;
        inputLoop(std::cin);
    }
    else if(argc > 1) {
        cursor = 1;
        inputLoop(argc, argv);
    }
    return 0;
}



