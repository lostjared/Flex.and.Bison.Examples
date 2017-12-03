#include<iostream>
#include<string>
#include"mxl.hpp"
#include<memory>


int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Error requires one argument..\n";
        exit(EXIT_FAILURE);
    }
    std::unique_ptr<mxl::MXL> parser(mxl::MXL::parseMXL(argv[1]));
    if(!parser) {
        std::cout << "Failed to parse source..\n";
        exit(EXIT_FAILURE);
    }
    parser->echoTokens();
    return 0;
}

