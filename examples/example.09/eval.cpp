#include"syntax-tree.hpp"


namespace ast {
    
    Symbol *eval(AST *node) {
        
        Symbol *s = new Symbol();
        
        switch(node->node_type) {
            case '+': {
                Symbol *s1 = eval(node->left), *s2 = eval(node->right);
                s->dvalue = s1->dvalue + s2->dvalue;
                return s;
            }
                break;
            case '$':
                return node->sym;
                break;
        }

        return s;
    }
    
    
}


