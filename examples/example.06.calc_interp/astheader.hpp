
#ifndef __AST__H__
#define __AST__H__

#include<iostream>
#include<string>

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

class Symbol;

class SymList {
public:
    Symbol *sym;
    SymList *next;
    SymList() : sym(0), next(0) {}
    SymList(Symbol *symbol, SymList *n) :sym(symbol), next(n) {}
};

class Symbol {
public:
    Symbol() : value(0), function(0), syms(0) {}
    Symbol(std::string n, double v) : name(n), value(v), function(0), syms(0) {}
    Symbol(std::string n, double v, AST *func, SymList *s) : name(n), value(v), function(func),syms(s) {}
    
    std::string name;
    double value;
    AST *function;
    SymList *syms;
};

enum FuncCall {
	FN_SQRT,
	FN_EXP,
    FN_LOG,
    FN_PRINT
};
class FnCall {
public:
    int node_type;
    AST *l;
    FuncCall func_b;
};

class UFnCall {
public:
    int node_type;
    AST *l;
    Symbol *s;
};

class Flow {
public:
    int node_type;
    AST *cond;
    AST *tl,*tr;
    
};

class NumVal {
public:
    int node_type;
    double number;
};

class SymRef {
public:
    int node_type;
    Symbol *s;
};

class SymEqual {
public:
    int node_type;
    Symbol *s;
    AST *v;
};

Symbol *getSymbol(const std::string &n);
AST *createAst(int node_type, AST *l, AST *r);
AST *createNum(double d);
AST *createCmp(int cmptype, AST *l, AST *r);
AST *createFunc(int func_type, AST *l);
AST *createCall(Symbol *s, AST *l);
AST *createRef(Symbol *s);
AST *createAssign(Symbol *s, AST *v);
AST *createFlow(int node_type,AST *cond, AST *tl, AST *tr);
SymList *createSymList(Symbol *s, SymList *next);
void doref(Symbol *name, SymList *lst, AST *statments);


double eval(AST *ast);
void freeAst(AST *node);
void SymList_Free(SymList *s);

#endif

