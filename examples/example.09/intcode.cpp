
#include "intcode.hpp"

namespace intcode {
    
    CODE_T code_info[] = {
        {"mov", CODE_INST::MOV, 2},
        {"push", CODE_INST::PUSH, 1},
        {"pop", CODE_INST::POP, 1},
        {"add", CODE_INST::ADD, 2},
        {"sub", CODE_INST::SUB, 2},
        {"mul", CODE_INST::MULT, 2},
        {"div", CODE_INST::DIV, 2},
        {"null", CODE_INST::NULL_CODE, 0}
    };
    
    int IntCode_LookupCode(const std::string &text) {
        for(unsigned int i = 0; code_info[i].code != CODE_INST::NULL_CODE; ++i) {
            if(code_info[i].text==text) return i;
        }
        return -1;
    }
    int IntCode_LookupCode(const CODE_INST &c) {
        for(unsigned int i = 0; code_info[i].code != CODE_INST::NULL_CODE; ++i) {
            if(code_info[i].code == c) return i;
        }
        return -1;
    }
    
    IntCode::IntCode(const CODE_INST &c) : code(c) {}
    
    IntCode::IntCode(const IntCode &ic) {
        code = ic.code;
        operands = ic.operands;
    }
    IntCode &IntCode::operator=(const IntCode &ic) {
        code = ic.code;
        operands = ic.operands;
        return *this;
    }
    
}
