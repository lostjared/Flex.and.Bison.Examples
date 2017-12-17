
#ifndef __TREE___H__
#define __TREE___H__
// Practice creating a tree.
// Than moving through the tree and solving the expression
#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>
#include<fstream>

void yyerror(const char *src, ...);
extern int yylineno;

struct Symbol {
    double value;
    std::string name;
    Symbol() : value(0) {}
    Symbol(std::string n, double v) : value(v), name(n) {}
};

enum class Var_type { EMPTY, DIGIT, VARIABLE, PLUS,MINUS,MIN,MULT,DIV,EQUAL};
extern std::unordered_map<std::string, Symbol> symbols;
extern std::ostringstream code_stream;
extern std::ostringstream var_stream;

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
    Node(Symbol *sym, Node<T> *value) {
        token = "=";
        id = Var_type::EQUAL;
        left = new Node<T>(sym->name, Var_type::VARIABLE, nullptr, nullptr);
        right = value;
        value = 0;
    }
};

template<typename T>
class Tree {
public:
    Node<T> *root;
    std::fstream output;
    Tree() {
        root = nullptr;
    }
    ~Tree() {
        if(root != nullptr)
        release(root);
        root = nullptr;
    }
    
    void print() {
        printNodes(root);
    }
    
    void outputCode(std::ostream &fobj) {
        var_stream.str("");
        fobj << "#include<stdio.h>\n#include<stdlib.h>\n#include<assert.h>\n";
        fobj << "double stack[5000];\n";
        fobj << "int stack_index = 0;\n";
        fobj << "\nvoid tr_push(double d) {\nassert(stack_index < 5000);\nstack[stack_index++] = d;\n}\n\n";
        fobj << "double tr_pop() {\nassert(stack_index >= 1);\nreturn stack[--stack_index];\n}\n\n";
        fobj << "\nvoid tr_add() {\ndouble y = tr_pop(), x = tr_pop();\ntr_push(x+y);\n}\n";
        fobj << "\nvoid tr_sub() {\ndouble y = tr_pop(), x = tr_pop();\ntr_push(x-y);\n}\n";
        fobj << "\nvoid tr_mult() {\ndouble y = tr_pop(), x = tr_pop();\ntr_push(x*y);\n}\n";
        fobj << "\nvoid tr_div() {\ndouble y = tr_pop(), x = tr_pop();\ntr_push(x/y);\n}\n";
        fobj << "int main() {\n";
        for(auto i = symbols.begin(); i != symbols.end(); ++i) {
            var_stream << "double " << i->first << " = 0;\n";
        }
        fobj << var_stream.str();
        fobj << code_stream.str();
        fobj << "return 0;\n}\n";
        
    }
    
    double eval() {
        double val = eval(root);
        std::fstream output;
        output.open("output.c", std::ios::out);
        if(!output.is_open()) {
            std::cerr << "Could not open output file: output.c\n";
            exit(EXIT_FAILURE);
        }
        outputCode(output);
        output.close();
        return val;
    }
    
    double eval(Node<T> *node) {
        if(node == nullptr) return 0;
        
        std::cout << node->token << " current Node.\n";
        double v = 0;
    
        switch(node->id) {
            case Var_type::MIN: {
                 v = -eval(node->left);
                code_stream << "tr_push(-tr_pop());\n";
                return v;
            }
                break;
            case Var_type::EQUAL: {
                v = eval(node->right);
                symbols[node->left->token].value = v;
                std::cout << node->left->token << " = " << v << "\n";
                code_stream << node->left->token << " = " << "tr_pop();\n";
                code_stream << "printf(\"result = %f\\n\"," <<  node->left->token << ");\n";
            }
                break;
            case Var_type::PLUS: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "+" << op2 << "\n";
                code_stream << "tr_add();\n";
                return op1+op2;
            }
                break;
            case Var_type::MINUS: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "-" << op2 << "\n";
                code_stream << "tr_sub();\n";
                return op1-op2;
            }
                break;
            case Var_type::MULT: {
                double op1 = eval(node->left);
                double op2 = eval(node->right);
                std::cout << op1 << "*" << op2 << "\n";
                code_stream << "tr_mult();\n";
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
                code_stream << "tr_div();\n";
                return op1/op2;
            }
                break;
            case Var_type::VARIABLE:
                v = symbols[node->token].value;
                std::cout << "Variable [" << node->token << "] := Value: [" << v << "]\n";
                code_stream << "tr_push(" << node->token << ");\n";
                break;
            case Var_type::DIGIT:
                v = node->value;
                std::cout << "Constant Value: [" << v << "]\n";
                code_stream << "tr_push(" << v << ");\n";
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
            std::cout << "released: " << n->token << "\n";
            delete n;
        }
    }
};

using StringTree = Tree<std::string>;
using StringNode = Node<std::string>;
extern StringTree ast;

#endif
