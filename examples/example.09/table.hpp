#ifndef __TABLE__H_
#define __TABLE__H_


#include<iostream>
#include<string>
#include<vector>
#include"tree.hpp"
#include<memory>

namespace sym {
    
    template<typename T>
    class SymbolTable {
    public:
        struct SymbolInfo {
            typename tree::Tree<T>::node_type *nptr;
            unsigned int depth;
            std::string name;
        };
        using value_type = T;
        using node_ptr = typename tree::Tree<T>::node_type;
        SymbolTable();
        SymbolTable(SymbolTable<T> &st);
        SymbolTable(SymbolTable<T> &&st);
        SymbolTable<T> &operator=(const SymbolTable<T> &st);
        SymbolTable<T> &operator=(SymbolTable<T> &&st);
        bool exisits(std::string n);
        void pushTree();
        void pushTree(const std::string &n);
        void popTree();
        void insertLevel(int level, std::string n, const T &type);
        void insertTop(std::string n, const T &type);
        void insertGlobal(std::string n, const T &type);
        int findScopeByName(const std::string &n);
        typename tree::Tree<T>::node_type *searchStack(std::string n);
        bool searchStack(std::string n, SymbolInfo *info);
        void printTable();
        tree::Tree<T> *getTree(int index);
        tree::Tree<T> *operator[](unsigned int index) { return tree_stack[index].get(); }
        size_t size() const { return tree_stack.size(); }
        std::vector<std::unique_ptr<tree::Tree<T>>> *operator->() { return &tree_stack; }
    private:
        std::vector<std::unique_ptr<tree::Tree<T>>> tree_stack;
    };
    
   
    
    template<typename T>
    SymbolTable<T>::SymbolTable(SymbolTable<T> &st) {
        tree_stack = st.tree_stack;
    }
    
    template<typename T>
    SymbolTable<T>::SymbolTable(SymbolTable<T> &&st) {
        tree_stack = std::move(st.tree_stack);
    }
    
    template<typename T>
    SymbolTable<T> &SymbolTable<T>::operator=(const SymbolTable<T> &st) {
        tree_stack = st.tree_stack;
        return *this;
    }
    template<typename T>
    SymbolTable<T> &SymbolTable<T>::operator=(SymbolTable<T> &&st) {
        tree_stack = std::move(st.tree_stack);
        return *this;
    }
    
    template<typename T>
    SymbolTable<T>::SymbolTable() {
        pushTree("Global");
    }
    
    template<typename T>
    void SymbolTable<T>::pushTree() {
        tree_stack.push_back(std::unique_ptr<tree::Tree<T>>(new tree::Tree<T>()));
    }
    
    template<typename T>
    void SymbolTable<T>::pushTree(const std::string &n) {
        pushTree();
        int level = tree_stack.size()-1;
        tree_stack[level]->setScope(n);
    }
    
    template<typename T>
    int SymbolTable<T>::findScopeByName(const std::string &n) {
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            if(tree_stack[i]->getScope() == n) return i;
        }
        return -1; // return -1 on failure to find
    }
    
    template<typename T>
    void SymbolTable<T>::popTree() {
#ifdef DEBUG_INFO
        int size = tree_stack.size()-1;
        if(size >= 0) {
            std::cout << "pop_back tree: " << tree_stack[size]->getScope() << "\n";
        }
#endif
        tree_stack.pop_back();
    }
    
    template<typename T>
    bool SymbolTable<T>::exisits(std::string n) {
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            typename tree::Tree<T>::node_type *node;
            node = tree_stack[i]->findNode(n);
            if(node != nullptr) return true;
        }
        return false;
    }
    
    template<typename T>
    typename tree::Tree<T>::node_type *SymbolTable<T>::searchStack(std::string n) {
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            typename tree::Tree<T>::node_type *node;
            node = tree_stack[i]->findNode(n);
            if(node != nullptr)
                return node;
            
        }
        return nullptr;
    }
    
    template<typename T>
    bool SymbolTable<T>::searchStack(std::string n, SymbolInfo *info) {
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            typename tree::Tree<T>::node_type *node;
            node = tree_stack[i]->findNode(n);
            if(node != nullptr) {
                info->depth = i;
                info->nptr = node;
                info->name = n;
                return true;
            }
        }
        return false;
    }
    
    template<typename T>
    void SymbolTable<T>::insertTop(std::string n, const T &type) {
        int top_level = tree_stack.size()-1;
        if(top_level >= 0 )
            tree_stack[top_level]->addItem(n, type);
    }
    
    template<typename T>
    void SymbolTable<T>::insertGlobal(std::string n, const T &type) {
        if(tree_stack.size()>0)
            tree_stack[0].addItem(n, type);
    }
    
    template<typename T>
    void SymbolTable<T>::insertLevel(int level, std::string n, const T &type) {
        if(level >= 0 && level < tree_stack.size()) {
            tree_stack[level]->addItem(n, type);
        }
    }
    
    template<typename T>
    void SymbolTable<T>::printTable() {
        std::cout << "<-**** Symbol Table ****->\n";
        for(int i = tree_stack.size()-1; i >= 0; --i) {
            std::cout << "Current Scope: " << tree_stack[i]->getScope() << " Depth Level: " << i << "\n";
            tree_stack[i]->printValues();
        }
        std::cout << "<-**** End Symbols ****->\n";
    }
    
    template<typename T>
    tree::Tree<T> *SymbolTable<T>::getTree(int index) {
        if(index >= 0 && index < tree_stack.size())
            return tree_stack[index].get();
        return nullptr;
    }
}

#endif

