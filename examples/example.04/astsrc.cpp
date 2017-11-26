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
            v = -eval(ast->left);
            break;
        default:
            yyerror("Error reached invalid node type: %d \n", ast->node_type);
            break;
    }
    
    return v;
}
void freeAst(AST *node) {
    switch(node->node_type) {
        case '+':
        case '-':
        case '*':
        case '/':
            freeAst(node->right);
        case '|':
        case 'M':
            freeAst(node->left);
        case 'K':
            delete node;
            break;
        default:
            std::cerr << "Error invalid node: " << node->node_type << "\n";
            break;
    }
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "%d: error ", yylineno);
    vfprintf(stderr, src, ap);
    fprintf(stderr, "\n");
}
