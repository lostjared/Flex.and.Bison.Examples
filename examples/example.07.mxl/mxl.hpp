
#ifndef __MXL___H__
#define __MXL___H__

#include<iostream>
#include<string>
#include<map>

extern void yyerror(const char *src, ...);
extern int yylineno;

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

extern std::map<std::string, std::string> vars;

void readSource();
void readSource(std::string data);
void echoTokens();

#endif

