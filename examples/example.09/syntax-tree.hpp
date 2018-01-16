#ifndef __SYNTAX_TREE 
#define __SYNTAX_TREE

#include"intcode.hpp"
#include<cstdarg>
#include"table.hpp"

namespace ast {
    
    enum { FN_EXIT, FN_PRINT, FN_SQRT };
    
    extern sym::SymbolTable<Symbol> sym_table;
    
    class DivideByZero {};
 
    class NodeType {
    public:
        std::string token;
        double value;
        // values here.
    };

    template<typename T>
    class AST_Node;
    
    template<typename T>
    class AST_Node {
    public:
        T type;
        Symbol *sym;
        unsigned int node_type;
        AST_Node *left, *right;
        
        AST_Node() : type(T()), sym(0), node_type(0), left(0), right(0) {}
        AST_Node(T ntype, unsigned int nnode_type, Symbol *s, AST_Node *nleft, AST_Node *nright) : type(type), node_type(nnode_type), sym(s), left(nleft), right(nright) {}
    };
    
    template<typename T>
    AST_Node<T> *createNode(T type, unsigned int node_type, Symbol *s, AST_Node<T> *left, AST_Node<T> *right) {
        AST_Node<T> *n = new AST_Node<T>(type,node_type,s,left,right);
        if(!n) {
            throw SymbolException("Error allocating memory...\n");
            return nullptr;
        }
        return n;
    }
    
    template<typename T>
    AST_Node<T> *createNode(unsigned int node_type, Symbol *s, AST_Node<T> *left, AST_Node<T> *right) {
        AST_Node<T> *n = new AST_Node<T>();
        if(!n) {
            throw SymbolException("Error allocating memory...\n");
            return nullptr;
        }
        n->node_type = node_type;
        n->sym = s;
        n->left = left;
        n->right = right;
        return n;
    }
    
    template<typename T>
    AST_Node<T> *createNode(T type, unsigned int node_type, AST_Node<T> *left, AST_Node<T> *right) {
        AST_Node<T> *n = new AST_Node<T>();
        if(!n) {
            throw SymbolException("Error allocating memory...\n");
            return nullptr;
        }
        n->type = type;
        n->node_type = node_type;
        n->left = left;
        n->right = right;
        return n;
    }
    
    template<typename T>
    AST_Node<T> *createNode(unsigned int node_type, AST_Node<T> *left, AST_Node<T> *right) {
        AST_Node<T> *n = new AST_Node<T>();
        if(!n) {
            throw SymbolException("Error allocating memroy...\n");
            return nullptr;
        }
        n->node_type = node_type;
        n->left = left;
        n->right = right;
        return n;
    }
    
    template<typename T>
    AST_Node<T> *createNodeValue(unsigned int value, Symbol *s) {
        AST_Node<T> *n = new AST_Node<T>();
        n->node_type = '$';
        n->sym = s;
        n->left = nullptr;
        n->right = nullptr;
        return n;
    }

    template<typename T>
    void freeAST(AST_Node<T> *node) {
        if(node != nullptr && node->left != nullptr)
            freeAST(node->left);
        if(node != nullptr && node->right != nullptr)
            freeAST(node->right);
        if(node != nullptr) {
            if(node->sym != nullptr && node->sym->free_memory == 0)
                delete node->sym;
            
            delete node;
            node = nullptr;
        }
    }
    
    using AST = AST_Node<NodeType>;
    Symbol *eval(AST *node);
    
}

extern int err_num;
extern int yylineno;
extern void yyerror(const char *str, ...);

#endif

