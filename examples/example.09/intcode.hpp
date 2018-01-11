
#ifndef __INTCODE__H__
#define __INTCODE__H__

#include<iostream>
#include<string>
#include<vector>

namespace intcode {
    
    enum CODE_INST { MOV, PUSH, POP, ADD, SUB, MULT, DIV };
    
    class Operand {
    public:
        
    };
    
    class IntCode {
    public:
        CODE_INST code;
        std::vector<Operand> operands;
    };
}

#endif


