
#ifndef __INTCODE__H__
#define __INTCODE__H__

#include<iostream>
#include<string>
#include<vector>

namespace intcode {
    
    enum CODE_INST { MOV, PUSH, POP, ADD, SUB, MULT, DIV };
    
    class Operand {
    public:
        std::string value;
        double dvalue;
        //...
    };
    
    class IntCode {
    public:
        CODE_INST code;
        std::vector<Operand> operands;
        
        IntCode(const CODE_INST &c);
    };
}

#endif


