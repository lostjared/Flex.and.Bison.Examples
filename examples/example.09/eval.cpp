/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */

#include"syntax-tree.hpp"
#include<sstream>
#include<cmath>

using namespace ast;

namespace ast {
    
    Symbol eval(AST *node) {
        Symbol s;
        unsigned int eval_node_type = node->node_type;
        switch(eval_node_type) {
            case '+': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                s.type = s1.type;
                if((s1.type == Symbol_Type::CONSTANT_NUMERIC || s1.type == Symbol_Type::NUMERIC) && (s2.type == Symbol_Type::CONSTANT_NUMERIC || s2.type == Symbol_Type::NUMERIC)) {
                    s.dvalue = s1.dvalue + s2.dvalue;
                }
                else if((s1.type == Symbol_Type::CONSTANT_STRING || s1.type == Symbol_Type::STRING) && (s2.type == Symbol_Type::CONSTANT_STRING || s2.type == Symbol_Type::STRING)) {
                    s.value = s1.value+s2.value;
                }
                else if((s1.type == Symbol_Type::CONSTANT_STRING || s1.type == Symbol_Type::STRING) && (s2.type == Symbol_Type::CONSTANT_NUMERIC || s2.type == Symbol_Type::NUMERIC)){
                    std::ostringstream stream;
                    stream << s1.value << s2.dvalue;
                    s.value = stream.str();
                } else if((s1.type == Symbol_Type::NUMERIC || s1.type == Symbol_Type::CONSTANT_NUMERIC) && (s2.type == Symbol_Type::STRING || s2.type == Symbol_Type::CONSTANT_STRING)) {
                    throw SymbolException("Invalid argument to expression, plus operator for Numeric requires Numeric");
                }
                return s;
            }
                break;
            case '-': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                s.dvalue = s1.dvalue - s2.dvalue;
                s.type = s1.type;
                return s;
            }
                break;
            case '*': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                s.dvalue = s1.dvalue * s2.dvalue;
                s.type = s1.type;
                return s;
            }
                break;
            case '/': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                if(s2.dvalue == 0)
                    throw ast::DivideByZero();
                
                s.dvalue = s1.dvalue / s2.dvalue;
                s.type = s1.type;
                return s;
            }
                break;
            case 'M': {
                Symbol v = eval(node->left);
                v.dvalue = -v.dvalue;
                return v;
            }
                break;
            case '$':
                return *node->sym;
                break;
            case 'S':
                return *node->sym;
                break;
            case 'N': {
                if(!sym_table.exisits(node->sym->name)) {
                    sym_table.insertTop(node->sym->name, *node->sym);
                }
                auto item = sym_table.searchStack(node->sym->name);
                item->value.name = item->id;
                return item->value;
            }
                break;
            case '=': {
                Symbol v = eval(node->left);
                if(!sym_table.exisits(node->sym->name)) {
                    if(v.type == Symbol_Type::CONSTANT_NUMERIC || v.type == Symbol_Type::NUMERIC)
                        v.type = Symbol_Type::NUMERIC;
                    else if(v.type == Symbol_Type::CONSTANT_STRING || v.type == Symbol_Type::STRING)
                        v.type = Symbol_Type::STRING;
                    v.name = node->sym->name;
                    sym_table.insertTop(node->sym->name, v);
                } else {
                    auto n = sym_table.searchStack(node->sym->name);
                    if(v.type == Symbol_Type::CONSTANT_NUMERIC || v.type == Symbol_Type::NUMERIC) {
                        v.type = Symbol_Type::NUMERIC;
                    }
                    else if(v.type == Symbol_Type::CONSTANT_STRING || v.type == Symbol_Type::STRING) {
                        v.type = Symbol_Type::STRING;
                    }
                    v.name = node->sym->name;
                    n->value = v;
                }
                return v;
            }
                break;
            case 'F': {
                if(node->sym != nullptr) {
                    unsigned int fn_type = node->sym->function.fn;
                    switch(fn_type) {
                        case FN_INPUT_STRING: {
                            std::string in_str;
                            std::getline(std::cin, in_str);
                            return Symbol(in_str);
                        }
                            break;
                        case FN_INPUT_NUMBER: {
                            double val = 0;
                            std::cin >> val;
                            return Symbol(val);
                        }
                            break;
                        case FN_SIN:
                        case FN_COS:
                        case FN_TAN: {
                            if(node->left != nullptr && node->left->node_type != 'L') {
                                Symbol value = eval(node->left);
                                switch(fn_type) {
                                    case FN_SIN:
                                         return Symbol(sin(value.dvalue));
                                        break;
                                    case FN_COS:
                                        return Symbol(cos(value.dvalue));
                                        break;
                                    case FN_TAN:
                                        return Symbol(tan(value.dvalue));
                                        break;
                                }
                            } else {
                                throw SymbolException("Function requires one numeric argument");
                            }
                            
                        }
                            break;
                        case FN_EXIT: {
                            if(node->left != nullptr && node->left->node_type != 'L') {
                                Symbol s = eval(node->left);
#ifdef DEBUG_INFO
                                std::cout << "Exiting error code: " << s.dvalue << "\n";
#endif
                                exit(static_cast<int>(s.dvalue));
                            } else {
                                throw SymbolException("exit requires one argment of error code");
                            }
                        }
                            break;
                        case FN_PRINTLN:
                        case FN_PRINT: {
                            std::string end;
                            if(node != nullptr && node->sym != nullptr)
                                end = (node->sym->function.fn == FN_PRINTLN) ? "\n" : "";
                            
                            AST *n = node;
                            if(n != nullptr && n->left != nullptr && n->left->node_type == 'L') {
                                n = n->left;
                                if(n != nullptr) {
                                    while(n != nullptr && n->left != nullptr) {
                                        Symbol sym = eval(n->left);
                                        printSymbol(sym, "");
                                        n = n->right;
                                    }
                                    if(n != nullptr) {
                                        Symbol sym = eval(n);
                                        printSymbol(sym, end);
                                    }
                                }
                                return Symbol(0);
                                
                            } else if(n != nullptr && n->left != nullptr) {
                                Symbol sym = eval(n->left);
                                printSymbol(sym, end);
                                return Symbol(0);
                            }
                        }
                            break;
                    }
                }
                break;
            }
        }
        return s;
    }
    
    void printSymbol(Symbol &s, std::string end) {
        switch(s.type) {
            case Symbol_Type::NUMERIC:
            case Symbol_Type::CONSTANT_NUMERIC:
                std::cout << s.dvalue << end;
                break;
            case Symbol_Type::STRING:
            case Symbol_Type::CONSTANT_STRING:
                std::cout << s.value << end;
                break;
            case Symbol_Type::EMPTY:
                break;
            case Symbol_Type::FUNCTION:
                break;
        }
    }
    
    
}


