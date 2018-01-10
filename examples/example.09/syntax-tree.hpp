#ifndef __SYNTAX_TREE 
#define __SYNTAX_TREE

#include"table.hpp"


namespace ast {
    
    enum { FN_EXIT, FN_PRINT, FN_SQRT };
    
    enum class Symbol_Type { STRING, NUMERIC, CONSTANT_STRING, CONSTANT_NUMERIC, FUNCTION };
    
    class NodeType {
    public:
        std::string token;
        // values here..
    };
    
    template<typename T>
    class AST_Node;
    
    class Symbol {
    public:
        Symbol(std::string name, std::string value);
        Symbol(std::string name, double d);
        Symbol(double d);
        Symbol(std::string value);
        
        std::string name,value;
        double dvalue;
        Symbol_Type type;
        bool variable;
        
        class Function {
        public:
            Function() : func(0), instruct(0) {}
            std::string name;
            void (*func)(std::vector<Symbol *> &);
            std::vector<Symbol *> args;
            AST_Node<NodeType> *instruct;
            
            void setFunction(std::string n_name, void (*f)(std::vector<Symbol *> &), std::vector<Symbol *> &n_args) {
                name = n_name;
                args = n_args;
                func = f;
            }
        };
        Function function;
    };
    
    Symbol *createSymbol(std::string name, std::string value);
    Symbol *createSymbol(std::string value);
    Symbol *createSymbol(double d);
    Symbol *createSymbol(std::string n, double v);

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
            std::cerr << "Error could not create node..\n";
            return nullptr;
        }
        return n;
    }
    
  
}

extern void yyerror(const char *str, ...);


#endif

