#include<iostream>
#include<algorithm>
#include<string>
#include "astheader.hpp"
#include "parser.tab.h"

extern void initLoop(std::istream &in);

void inputLoop(std::istream &in);

int main() {
    inputLoop(std::cin);
    return 0;
}



