#include "astheader.hpp"
#include<iostream>
#include<cstdlib>
#include<unordered_map>
#include<cstdarg>
#include<cmath>

std::unordered_map<std::string, Symbol *> symbols;


AST *createAst(int node_type, AST *l, AST *r) {
    AST *a = new AST(node_type, l, r, 0);
    if(!a) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    return a;
}
AST *createNum(double d) {
    AST *n = new AST('K', d);
    if(!n) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
     return n;
}
double CallBuiltIn(FnCall *fn) {
    FuncCall fb = fn->func_b;
    double v = 0;
    if(fn->args >= 1) {
        v = eval(fn->l);
        switch(fb) {
            case FN_SQRT:
                return sqrt(v);
            case FN_EXP:
                return exp(v);
            case FN_LOG:
                return log(v);
            case FN_PRINT:
                std::cout << "Value: "  << v << "\n";
                break;
            case FN_EXIT:
                std::cout << "Exiting with code: " << (unsigned int)v << "\n";
                exit((unsigned int)v);
                return v;
            default:
                break;
        }
    } else {
        switch(fb) {
            case FN_INPUT:
                double d;
                std::cout << "Input >";
                std::cin >> d;
                return d;
            default:
                break;
        }
    }
    return 0;
}
double CallUser(UFnCall *ufn) {
    Symbol *fn = ufn->s;
    SymList *sl;
    AST *args = ufn->l;
    double *oldval, *newval;
    double v;
    int nargs;
    int i;
    if(!fn->function) {
        yyerror("Function not found..\n");
        return 0;
    }
    sl = fn->syms;
    for(nargs = 0; sl; sl = sl->next)
        nargs++;
    
    oldval = new double[nargs];
    newval = new double[nargs];
    
    if(!oldval || !newval) {
        yyerror("Out of space..\n");
        return 0.0;
    }
    
    for(i = 0; i < nargs; ++i) {
        if(!args) {
            yyerror("Invalid arguments..\n");
            delete [] oldval;
            delete [] newval;
            return 0;
        }
        
        if(args->node_type == 'L') {
            newval[i] = eval(args->left);
            args = args->right;
        } else {
            newval[i] = eval(args);
            args = NULL;
        }
    }
    sl = fn->syms;
    for( i = 0; i < nargs; i++) {
        Symbol *s = sl->sym;
        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl->next;
    }
    
    delete [] newval;
    
    v = eval(fn->function);
    
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        Symbol *s = sl->sym;
        s->value = oldval[i];
        sl = sl->next;
    }
    
    delete [] oldval;
    return v;
}

double eval(AST *ast) {
    if(!ast) return 0;
    double v = 0;
    switch(ast->node_type) {
        case 'K': {
            v = ast->number;
            return v;
        }
        case 'N':
            v = ((SymRef*)ast)->s->value;
            break;
        case '=': {
            v = ((SymEqual*)ast)->s->value = eval( ((SymEqual*)ast)->v);
        }
            break;
        case '+': {
           	v = eval(ast->left) + eval(ast->right);
        }
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
        case '1':
            v = (eval(ast->left) > eval(ast->right)) ? 1 : 0;
            break;
        case '2':
            v = (eval(ast->left) < eval(ast->right)) ? 1 : 0;
            break;
        case '3':
            v = (eval(ast->left) != eval(ast->right)) ? 1 : 0;
            break;
        case '4':
            v = (eval(ast->left) == eval(ast->right)) ? 1 : 0;
            break;
        case '5':
            v = (eval(ast->left) >= eval(ast->right)) ? 1 : 0;
            break;
        case '6':
            v = (eval(ast->left) <= eval(ast->right)) ? 1 : 0;
            break;
        case 'I':
            if(eval(((Flow *)ast)->cond) != 0) {
                if (((Flow*)ast)->tl)
                    v = eval(((Flow*)ast)->tl);
                else
                    v = 0.0;
            } else {
                if(((Flow*)ast)->tr)
                    v = eval(((Flow*)ast)->tr);
                else
                    v = 0.0;
            }
            break;
        case 'W':
            v = 0.0;
            if(((Flow*)ast)->tl) {
                while(eval(((Flow*)ast)->cond) != 0) {
                    v = eval(((Flow*)ast)->tl);
                }
            }
            break;
            
        case 'L':
            eval(ast->left); v = eval(ast->right);
            break;
        case 'F':
            v = CallBuiltIn(((FnCall*)ast));
            break;
        case 'C':
            v = CallUser(((UFnCall*)ast));
            break;
        default:
            yyerror("Error reached invalid node type: %d [%c] \n", ast->node_type, ast->node_type);
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
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case 'L':
            freeAst(node->right);
        case '|':
        case 'M':
        case 'C':
        case 'F':
            freeAst(node->left);
        case 'K':
        case 'N':
            break;
        case '=': {
            // delete node
            SymEqual *equal = (SymEqual *)node;
            delete equal->v;
        }
            break;
        case 'I':
        case 'W': {
            Flow *w = (Flow*)node;
            delete w->cond;
            if(w->tl != 0) freeAst(w->tl);
            if(w->tr != 0) freeAst(w->tr);
        }
            break;
        default:
            yyerror("Error invalid node: %d \n", node->node_type);
            break;
    }
    delete node;
}

Symbol *getSymbol(const std::string &n) {

    if(symbols.find(n) == symbols.end()) {
        Symbol *s = new Symbol();
        s->name = n;
        symbols[n] = s;
        return s;
    }
    return symbols[n];
}

AST *createCmp(int cmptype, AST *l, AST *r) {
    AST *n = new AST();
    if(!n) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    n->node_type = '0' + cmptype;
    n->left = l;
    n->right = r;
    return n;
}
AST *createFunc(int func_type, AST *l) {
    FnCall *fn = new FnCall();
    if(!fn) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    fn->node_type = 'F';
    fn->l = l;
    fn->func_b = (FuncCall)func_type;
    fn->args = 1;
    return (AST*)fn;
}

AST *createFuncNoArgs(int func_type) {
    FnCall *fn = new FnCall();
    if(!fn) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    fn->node_type = 'F';
    fn->l = 0;
    fn->func_b = (FuncCall)func_type;
    fn->args = 0;
    return (AST*)fn;
}

AST *createCall(Symbol *s, AST *l) {
    UFnCall *fn = new UFnCall();
    if(!fn) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    fn->node_type = 'C';
    fn->l = l;
    fn->s = s;
    return (AST*)fn;
}
AST *createRef(Symbol *s) {
    SymRef *ref = new SymRef();
    if(!ref) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    ref->s = s;
    ref->node_type = 'N';
    return (AST*)ref;
}
AST *createAssign(Symbol *s, AST *v) {
    SymEqual *equal = new SymEqual();
    if(!equal) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    equal->node_type = '=';
    equal->s = s;
    equal->v = v;
    return (AST*)equal;
}
AST *createFlow(int node_type,AST *cond, AST *tl, AST *tr) {
    Flow *flow = new Flow();
    if(!flow) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    flow->node_type = node_type;
    flow->cond = cond;
    flow->tl = tl;
    flow->tr = tr;
    return (AST*)flow;
}

SymList *createSymList(Symbol *s, SymList *next) {
    SymList *sl = new SymList();
    if(!sl) {
        yyerror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    sl->sym = s;
    sl->next = next;
    return sl;
}

void doref(Symbol *name, SymList *lst, AST *statements) {
    if(name->syms) SymList_Free(name->syms);
    if(name->function) freeAst(name->function);
    name->syms = lst;
    name->function = statements;
}

void SymList_Free(SymList *sl) {
    SymList *nsl;
    while(sl) {
        nsl = sl->next;
        delete sl;
        sl = nsl;
    }
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Line %d: error ", yylineno);
    vfprintf(stderr, src, ap);
}
