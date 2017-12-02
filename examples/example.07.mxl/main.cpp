#include<iostream>
#include<string>
#include"mxl.hpp"



int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Error requires one argument..\n";
        exit(EXIT_FAILURE);
    }
    readSource(argv[1]);
    echoTokens();
    return 0;
}

