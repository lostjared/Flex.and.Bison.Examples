
#ifndef __AST__H__
#define __AST__H__

extern int yylineno;
void yyerror(const char *s, ...);

extern int yylex();

struct AST {
    int node_type;
    AST *left, *right;
    double number;
    AST() : node_type(0), left(0), right(0), number(0) { }
    AST(int node, AST *l, AST *r, double n) : node_type(node), left(l), right(r), number(n) {}
    AST(int node, double n) : node_type(node), left(0), right(0), number(n) {}
};


AST *createAst(int node_type, AST *l, AST *r);
AST *createNum(double d);

double eval(AST *ast);
void freeAst(AST *node);

#endif

