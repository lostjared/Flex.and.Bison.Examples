
#ifndef __INTCODE__H__
#define __INTCODE__H__

#include<iostream>
#include<string>
#include<vector>

namespace intcode {
    
    enum class CODE_INST { MOV=1, PUSH, POP, ADD, SUB, MULT, DIV, NULL_CODE};
    
    class Operand {
    public:
        std::string value;
        double dvalue;
        //...
    };
    
    struct CODE_T {
        std::string text;
        CODE_INST code;
        unsigned int num_args;
    };
    
    extern CODE_T code_info[];
    
    int IntCode_LookupCode(const std::string &text);
    int IntCode_LookupCode(const CODE_INST &c);
    
    class IntCode {
    public:
        CODE_INST code;
        std::vector<Operand> operands;
        unsigned int num_op;
        
        IntCode(const CODE_INST &c);
        IntCode(const IntCode &ic);        
        IntCode &operator=(const IntCode &ic);
    };
}

#endif


