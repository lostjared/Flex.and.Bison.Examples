
#ifndef __TREE___H__
#define __TREE___H__
// Practice creating a tree.
// Than moving through the tree and solving the expression
#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>
#include<fstream>
#include<vector>
#include<cassert>

enum UFN_TYPE {
    FN_PRINT,
    FN_EXIT
};

void yyerror(const char *src, ...);
std::string trimQuotes(std::string value);
extern int yylineno;
extern int err_num;

enum class Var_id { ID_NUMERIC, ID_STRING };

struct Symbol {
    double value;
    std::string name;
    std::string str_value;
    Var_id vtype;
    Symbol() : value(0) {}
    Symbol(std::string n, double v) : value(v), name(n), vtype(Var_id::ID_NUMERIC) {}
    Symbol(std::string n, std::string val) : name(n), str_value(val), value(0), vtype(Var_id::ID_STRING) {}
};

enum class Var_type { EMPTY, DIGIT, VARIABLE, PLUS,MINUS,MIN,MULT,DIV,EQUAL, BFUNCTION, ARG, STRING, PRINTFUNC};
extern std::unordered_map<std::string, Symbol> symbols;
extern std::ostringstream code_stream;
extern std::ostringstream var_stream;

template<typename T>
class Node {
public:
    T token;
    double value;
    Var_type id;
    int bfunc;
    Symbol *sym;
    Node<T> *left, *right;
    
    ~Node() {
        if(sym != nullptr) delete sym;
        sym = nullptr;
    }
    
    Node() : id(Var_type::EMPTY), left(nullptr), right(nullptr), sym(nullptr) {}
    Node(const T &n_token, Var_type n_id, Node<T> *n_left, Node<T> *n_right) {
        token = n_token;
        id = n_id;
        left = n_left;
        right = n_right;
        value = 0;
        sym = nullptr;
    }
    Node(double d) {
        value = d;
        id = Var_type::DIGIT;
        std::ostringstream stream;
        stream << d;
        token = stream.str();
        left = nullptr;
        right = nullptr;
        sym = nullptr;
    }
    Node(Symbol *s) {
        token = s->name;
        value = s->value;
        id = Var_type::VARIABLE;
        left = nullptr;
        right = nullptr;
        sym = s;
    }
    Node(Symbol *sym, Node<T> *v) {
        token = "=";
        id = Var_type::EQUAL;
        left = new Node<T>(sym->name, Var_type::VARIABLE, nullptr, nullptr);
        right = v;
        value = 0;
        this->sym = sym;
    }
    Node(int print_func, Node<T> *func) {
        bfunc = print_func;
        id = Var_type::BFUNCTION;
        left = func;
        token = "F";
        value = 0;
        sym = nullptr;
    }
    Node(Node<T> *val, Symbol *s) {
        sym = s;
        id = Var_type::PRINTFUNC;
        left = nullptr;
        right = nullptr;
        value = 0;
        token = "PRINT";
    }
    
};

using StringNode = Node<std::string>;

template<typename T>
class Tree {
public:
    Node<T> *root;
    
    Tree() : root(nullptr) {
        
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
        fobj << "#define STACK_SIZE 5000\n";
        fobj << "#define tr_push(val) assert(stack_index < STACK_SIZE-1); stack[stack_index++] = val\n";
        fobj << "#define q_pop(val) assert(stack_index >= 1); val = stack[--stack_index]\n\n";
        fobj << "double stack[STACK_SIZE];\n";
        fobj << "int stack_index = 0;\n\n";
        fobj << "double tr_pop() {\nassert(stack_index >= 1);\nreturn stack[--stack_index];\n}\n\n";
        fobj << "\nvoid tr_add() {\n double x,y; q_pop(y); q_pop(x); tr_push(x+y); \n}\n";
        fobj << "\nvoid tr_sub() {\n double x,y; q_pop(y); q_pop(x); tr_push(x-y); \n}\n";
        fobj << "\nvoid tr_mult() {\n double x,y; q_pop(y); q_pop(x); tr_push(x*y); \n}\n";
        fobj << "\nvoid tr_div() {\n double x,y; q_pop(y); q_pop(x); tr_push(x/y); \n}\n";
        fobj << "\n\n";
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
                code_stream << "q_pop(" << node->left->token << ");\n";
                code_stream << "printf(\"%s = %f\\n\"," << "\"" << node->left->token.c_str() << "\"" << "," << node->left->token << ");\n";
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
            case Var_type::ARG: {
                std::cout << "Argument value: " << node->left->token << "\n";
                return eval(node->left);
            }
                break;
            case Var_type::PRINTFUNC: {
                if(node->sym->name == "VAR_const") {
                	std::cout << node->sym->str_value << "\n";
                	code_stream << "printf(\"%s\\n\", " << node->sym->str_value << ");\n";
                } else {
                    code_stream << "printf(\"%s\\n\", " << node->sym->name << ");\n";
                }
            }
                break;
            case Var_type::BFUNCTION: {
                //v = builtinFunc(node);
                switch(node->bfunc) {
                    case FN_PRINT: {
                        //double v = eval(node->left);
                        /*
                        unsigned int counter = 0;
                        Args(node->left, &counter);
                        std::cout << "Value [" << v << "]\n";
                        code_stream << "printf(\"Values[";
                        for(unsigned int i = 0; i < counter; ++i)
                            code_stream << " %f ";
                        code_stream << "]\\n\",";
                        for(int i = counter; i > 1; --i)
                            code_stream << "stack[stack_index-" << i << "]" << ",";
                        code_stream << "stack[stack_index-1]);\n";
                        code_stream << "stack_index -=" << counter << ";\n"; */
                        return 0;
                    }
                        break;
                    case FN_EXIT: {
                        double v = eval(node->left);
                        unsigned int code_exit = static_cast<unsigned int>(v);
                        std::cout << "Exiting with Code: " << code_exit << "\n";
                    	exit(code_exit);
                    }
                        break;
                }
            }
                break;
            case Var_type::EMPTY:
                break;
            default:
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
            std::cout << "released: " << "[" << n->token << ":" << n->value << "]" << " := Token ID [" << int(n->id) << "]\n";
              delete n;
        }
    }
};

using StringTree = Tree<std::string>;
extern StringTree ast;

#endif
