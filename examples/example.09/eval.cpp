#include"syntax-tree.hpp"

using namespace ast;

namespace ast {
    
    Symbol eval(AST *node) {
        Symbol s;
        switch(node->node_type) {
            case '+': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                s.dvalue = s1.dvalue + s2.dvalue;
                return s;
            }
            	break;
            case '-': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                s.dvalue = s1.dvalue - s2.dvalue;
                return s;
            }
                break;
            case '*': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                s.dvalue = s1.dvalue * s2.dvalue;
                return s;
            }
                break;
            case '/': {
                Symbol s1 = eval(node->left), s2 = eval(node->right);
                if(s2.dvalue == 0)
                    throw ast::DivideByZero();
                
                s.dvalue = s1.dvalue / s2.dvalue;
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
            case 'N': {
                if(!sym_table.exisits(node->sym->name)) {
                	sym_table.insertTop(node->sym->name, *node->sym);
                }
                return sym_table.searchStack(node->sym->name)->value;
            }
            case '=': {
                Symbol v = eval(node->left);
                if(!sym_table.exisits(node->sym->name)) {
                    sym_table.insertTop(node->sym->name, v);
                } else {
                    sym_table.searchStack(node->sym->name)->value = v;
                }
                return v;
            }
                break;
        }
        return s;
    }
    
    
}


