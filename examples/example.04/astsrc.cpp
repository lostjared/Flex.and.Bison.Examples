#include "astheader.hpp"
#include<iostream>
#include<cstdlib>

AST *createAst(int node_type, AST *l, AST *r) {
    AST *a = new AST(node_type, l, r, 0);
    if(!a) {
        std::cerr << "Out of space...\n";
        exit(EXIT_FAILURE);
    }
    return a;
}
AST *createNum(double d) {
    AST *n = new AST('K', d);
    if(!n) {
        std::cerr << "Error couldn't allocate memory..\n";
        exit(EXIT_FAILURE);
    }
     return n;
}

double eval(AST *ast) {
    if(!ast) return 0;
    double v = 0;
    switch(ast->node_type) {
        case 'K': {
            v = ast->number;
            return v;
        }
        case '+':
            v = eval(ast->left) + eval(ast->right);
            break;
        case '-':
            v = eval(ast->left) - eval(ast->right);
            break;
        case '*':
            v = eval(ast->left) * eval(ast->right);
            break;
        case '/':
            v = eval(ast->left) / eval(ast->right);
            break;
        case '|':
            v = eval(ast->left);
            if(v < 0) v = -v;
            break;
        case 'M':
            break;
        default:
            yyerror("Error reached end..\n");
            break;
    }
    
    return v;
}
void freeAst(AST *node) {
    if(node != 0 && node->left != 0)
        freeAst(node->left);
    if(node != 0 && node->right != 0)
    	freeAst(node->right);
    
    if(node != 0)
    	delete node;
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "%d: error ", yylineno);
    vfprintf(stderr, src, ap);
    fprintf(stderr, "\n");
}
