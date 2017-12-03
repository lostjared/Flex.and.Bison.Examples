#include<iostream>
#include<string>
#include"mxl.hpp"
#include<memory>


int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Error requires one argument..\n";
        exit(EXIT_FAILURE);
    }
    // if running multiple threads lock mutex here
    std::unique_ptr<mxl::MXL> parser(mxl::MXL::parseMXL(argv[1]));
    // release here
    if(!parser) {
        std::cout << "Failed to parse source..\n";
        exit(EXIT_FAILURE);
    }
    if(parser->keyValid("Size", "int")) {
        std::string val = parser->table("Size", "int");
        std::cout << "Found Size value is: " << val << "\n";
    }
    parser->echoTokens();
    return 0;
}

