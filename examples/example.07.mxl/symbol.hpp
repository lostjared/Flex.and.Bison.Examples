
#ifndef __SYMBOL__H__
#define __SYMBOL__H__

#include<string>

class Symbol {
public:
    Symbol(std::string name_) : name(name_) {}
    std::string name;
};

class List {
public:
    Symbol *s;
    List(Symbol *v) : s(v) {}
    List *next;
};

#endif


