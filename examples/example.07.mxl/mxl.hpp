#ifndef __MXL___H__
#define __MXL___H__

#include<iostream>
#include<string>
#include<map>
#include "symbol.hpp"

extern void yyerror(const char *src, ...);
extern int yylineno;
extern std::string current_name;





extern std::map<std::string, std::map<std::string, std::string> > vars;
void readSource();
void readSource(std::string data);
void echoTokens();
std::string &getValue(std::string tag, std::string key);
std::string trimQuotes(std::string value);
#endif

