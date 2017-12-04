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

namespace mxl {
    class MXL {
        MXL() {}
    public:
        MXL(const std::map<std::string, std::map<std::string, std::string>> &v);
        MXL(std::map<std::string, std::map<std::string, std::string>> &&v);
        MXL(const MXL &m);
        MXL(MXL &&m);
        MXL &operator=(const MXL &m);
        MXL &operator=(MXL &&m);
        std::string &operator()(std::string cat, std::string key);
        std::string &table(std::string cat, std::string key);
        void setValue(std::string cat, std::string key, std::string val);
        void echoTokens();
        bool writeToFile(std::string filename);
//        void sortedWriteToFile(std::string filename);
        static MXL *parseMXL(const std::string &n);
        bool keyValid(const std::string &cat, const std::string &key);
        std::map<std::string, std::map<std::string, std::string>> &map() { return vars; }
    private:
        std::map<std::string, std::map<std::string, std::string>> vars;
    };
    
    void readSource();
    bool readSource(std::string data);
    void echoTokens();
    std::string &getValue(std::string tag, std::string key);
    std::string trimQuotes(std::string value);
}

#endif

