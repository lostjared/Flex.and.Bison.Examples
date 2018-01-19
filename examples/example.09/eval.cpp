#include"syntax-tree.hpp"
#include<sstream>
using namespace ast;

namespace ast {
    
    Symbol eval(AST *node) {
        Symbol s;
        switch(node->node_type) {
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
                return sym_table.searchStack(node->sym->name)->value;
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
                        n->value.type = Symbol_Type::NUMERIC;
                    }
                    else if(v.type == Symbol_Type::CONSTANT_STRING || v.type == Symbol_Type::STRING) {
                        n->value.type = Symbol_Type::STRING;
                    }
                    n->value = v;
                }
                return v;
            }
                break;
        }
        return s;
    }
    
    
}


