#include<iostream>
#include<algorithm>
#include<string>
#include "astheader.hpp"
#include "parser.tab.h"

extern int yyparse();
typedef unsigned long *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string (const char *yy_str  );
extern void yy_delete_buffer (YY_BUFFER_STATE);
extern void releaseBuffer();

void inputLoop(std::istream &in);

int main() {
    inputLoop(std::cin);
    return 0;
}


void inputLoop(std::istream &in) {
    std::cout << "$> ";
    while(!in.eof()) {
        std::string value;
        std::getline(in, value);
        YY_BUFFER_STATE buffer;
        if(in && value.length() > 0) {
            value += "\n\0";
        	buffer = yy_scan_string((char*)value.c_str());
        	yyparse();
            releaseBuffer();
        } else {
            std::cout << "$> ";
        }
    }
}
