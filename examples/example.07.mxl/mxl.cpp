#include "mxl.hpp"
#include<algorithm>

extern int yyparse();
extern void yyrestart(FILE *);
std::map<std::string, std::map<std::string, std::string> > vars;
std::string current_name="default";

std::string trimQuotes(std::string value) {
    if(value[0] == '\"' && value.length()>=2) {
        std::string temp;
        temp = value.substr(1, value.length()-2);
        return temp;
    }
    return value;
}

std::string &getValue(std::string tag, std::string key) {
    return vars[tag][key];
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Line %d: error  ", yylineno);
    vfprintf(stderr, src, ap);
    fprintf(stderr, "\n");
}

void readSource() {
    yyparse();
}

void readSource(std::string data) {
    FILE *fptr = fopen(data.c_str(), "r");
    if(!fptr) {
        std::cerr << "Error oculd not open file: " << data << "\n";
        exit(EXIT_FAILURE);
    }
    yyrestart(fptr);
    readSource();
    fclose(fptr);
}

void echoTokens() {
    std::map<std::string, std::map<std::string, std::string> >::iterator it;
    std::map<std::string, std::string>::iterator n;
    for(it = vars.begin(); it != vars.end(); it++) {
        std::cout << "Start Tag: [" << it->first << "]\n";
        for(n = it->second.begin(); n != it->second.end(); n++) {
            std::cout << "Key: [" << n->first << "] := " << n->second << "\n";
        }
    }
}
