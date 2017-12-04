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
        std::cout << "Found: " << mxl::error_count << " error(s).\n";
        exit(EXIT_FAILURE); // here you can signal the user file is not correct
    }
    if(parser->keyValid("Size", "int")) {
        std::string val = parser->table("Size", "int");
        std::cout << "Found Size value is: " << val << "\n";
    }
    parser->setValue("cat", "rat", "bat");
    parser->echoTokens();
    if(parser->sortedWriteToFile("test.mxl")) {
        std::cout << "Wrote to file: test.mxl\n";
    }
    return 0;
}

