
#ifndef __TREE___H__
#define __TREE___H__

// Practice creating a tree.
// Than moving through the tree and solving the expression
#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>

void yyerror(const char *src, ...);
extern int yylineno;

struct Symbol {
    double value;
    std::string name;
    Symbol() : value(0) {}
    Symbol(std::string n, double v) : value(v), name(n) {}
};

enum class Var_type { EMPTY, DIGIT, VARIABLE, PLUS,MINUS,MULT,DIV,EQUAL};
extern std::unordered_map<std::string, Symbol> symbols;

template<typename T>
class Node {
public:
    T token;
    double value;
    Var_type id;
    Node<T> *left, *right;
    Node() : id(Var_type::EMPTY), left(nullptr), right(nullptr) {}
    Node(const T &n_token, Var_type n_id, Node<T> *n_left, Node<T> *n_right) {
        token = n_token;
        id = n_id;
        left = n_left;
        right = n_right;
    }
    Node(double d) {
        value = d;
        id = Var_type::DIGIT;
        std::ostringstream stream;
        stream << d;
        token = stream.str();
        left = nullptr;
        right = nullptr;
    }
    Node(Symbol *s) {
        token = s->name;
        value = s->value;
        id = Var_type::VARIABLE;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class Tree {
public:
    Node<T> *root;
    
    Tree() {
        root = nullptr;//new Node<T>("Root", Var_type::EMPTY, nullptr, nullptr);
    }
    ~Tree() {
        if(root != nullptr)
        release(root);
        root = nullptr;
    }
    
    void print() {
        printNodes(root);
    }
    
    double eval() {
        return eval(root);
    }
    
    double eval(Node<T> *node) {
        if(node == nullptr) return 0;
        std::cout << node->token << " current Node..\n";
        double v = 0;
    
        switch(node->id) {
            case Var_type::EQUAL: {
                v = eval(node->right);
                symbols[node->left->token].value = v;
                std::cout << node->left->token << " = " << v << "\n";
            }
                break;
            case Var_type::PLUS: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "+" << op2 << "\n";
                return op1+op2;
            }
                break;
            case Var_type::MINUS: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "-" << op2 << "\n";
                return op1-op2;
            }
                break;
            case Var_type::MULT: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "*" << op2 << "\n";
                return op1*op2;
            }
                break;
            case Var_type::DIV: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                if(op2 == 0) {
                    std::cerr << "Error divde by zero.\n";
                    return 0;
                }
                std::cout << op1 << "/" << op2 << "\n";
                return op1/op2;
            }
                break;
                
                
            case Var_type::VARIABLE:
                v = symbols[node->token].value;
                std::cout << "Var Value: " << v << "\n";
                break;
            case Var_type::DIGIT:
                v = node->value;
                std::cout << "Value: " << v << "\n";
                break;
            case Var_type::EMPTY:
                break;
        }
        return v;
    }
    
    void release() {
        if(root != nullptr)
        release(root);
        root = nullptr;
    }
    
private:
    void printNodes(Node<T> *n) {
        if(n != nullptr)
            std::cout << "Node: " << n->token << ":" << static_cast<char>(n->id) << "\n";
        
        if(n != nullptr && n->left != nullptr)
            printNodes(n->left);
        
        if(n != nullptr && n->right != nullptr)
            printNodes(n->right);
    }
    
    void release(Node<T> *n) {
        if(n != nullptr && n->left != nullptr)
            release(n->left);
        if(n != nullptr && n->right != nullptr)
            release(n->right);
        if(n != nullptr) {
            std::cout << "releasing: " << n->token << "\n";
            delete n;
        }
    }
};

using StringTree = Tree<std::string>;
using StringNode = Node<std::string>;

extern StringTree ast;


#endif
