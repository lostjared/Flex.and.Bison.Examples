
#ifndef __AST__H__
#define __AST__H__

extern int yylineno;
void yyerror(const char *s, ...);

extern int yylex();

struct AST {
    int node_type;
    AST *left, *right;
    double number;
};


AST *createAst(int node_type, AST *l, AST *r);
AST *createNum(double d);

double eval(AST *ast);
void freeAst(AST *node);

#endif

