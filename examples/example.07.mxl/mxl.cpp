#include "mxl.hpp"
#include<algorithm>
#include<fstream>
#include<vector>

extern int yyparse();
extern void yyrestart(FILE *);
std::map<std::string, std::map<std::string, std::string> > vars;
std::string current_name="default";

namespace mxl {
    
    int error_count = 0;
    
    MXL::MXL(const std::map<std::string, std::map<std::string, std::string>> &v) {
        vars = v;
    }
    
    MXL::MXL(std::map<std::string, std::map<std::string, std::string>> &&v) {
        vars = std::move(v);
    }
    
    MXL::MXL(const MXL &m) {
        vars = m.vars;
    }
    MXL::MXL(MXL &&m) {
        vars = std::move(m.vars);
    }
    MXL &MXL::operator=(const MXL &m) {
        vars = m.vars;
        return *this;
    }
    MXL &MXL::operator=(MXL &&m) {
        vars = std::move(m.vars);
        return *this;
    }
    
    MXL *MXL::parseMXL(const std::string &n) {
        if(!readSource(n)) return nullptr;
        MXL *m = new MXL(::vars);
        if(!m) {
            std::cerr << "Error allocating memory quitting...\n";
            return nullptr;
        }
        if(!::vars.empty())
        	::vars.erase(::vars.begin(), ::vars.end());
        return m;
    }
    
    std::string &MXL::operator()(std::string cat, std::string key) {
        return vars[cat][key];
    }
    
    std::string &MXL::table(std::string cat, std::string key) {
        return vars[cat][key];
    }
    
    bool MXL::keyValid(const std::string &cat, const std::string &key) {
        auto i = vars.find(cat);
        if(i == vars.end())
            return false;
        auto t = i->second.find(key);
        if(t == i->second.end())
        	return false;
        return true;
    }
    
    void MXL::setValue(std::string cat, std::string key, std::string val) {
        vars[cat][key] = val;
    }
    
    void MXL::echoTokens() {
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        std::map<std::string, std::string>::iterator n;
        for(it = vars.begin(); it != vars.end(); it++) {
            std::cout << "Start Tag: [" << it->first << "]\n";
            for(n = it->second.begin(); n != it->second.end(); n++) {
                std::cout << "Key: [" << n->first << "] := " << n->second << "\n";
            }
        }
    }
    
    bool MXL::writeToFile(std::string filename) {
        std::fstream file;
        file.open(filename, std::ios::out);
        if(!file.is_open())
            return false;
        for(auto i = vars.begin(); i != vars.end(); ++i) {
            file << i->first << " => \n";
            for(auto j = i->second.begin(); j != i->second.end(); ++j) {
                file << j->first << " = \"" << j->second << "\"\n";
            }
            file << "\n";
        }
        file.close();
        return true;
    }
    
    bool MXL::sortedWriteToFile(std::string filename) {
        std::fstream file;
        file.open(filename, std::ios::out);
        if(!file.is_open())
            return false;
        std::vector<std::string> cat_keys, keys;
        for(auto i = vars.begin(); i != vars.end(); ++i) {
            cat_keys.push_back(i->first);
        }
        sort(cat_keys.begin(), cat_keys.end());
        for(auto i = cat_keys.begin(); i != cat_keys.end(); ++i) {
            if(!keys.empty()) keys.erase(keys.begin(), keys.end());
            for(auto z = vars[*i].begin(); z != vars[*i].end(); ++z) {
                keys.push_back(z->first);
            }
            std::sort(keys.begin(), keys.end());
            file << *i << " =>\n";
            for(auto z = keys.begin(); z != keys.end(); ++z) {
                file << *z << " = \"" << vars[*i][*z] << "\"\n";
            }
            file << "\n";
        }
        return true;
    }
    
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

    bool readSource() {
        if(yyparse() == 0 && error_count == 0)
            return true;
        return false;
    }
    
    bool readSource(std::string data) {
        error_count = 0;
        FILE *fptr = fopen(data.c_str(), "r");
        if(!fptr) {
            std::cerr << "Error oculd not open file: " << data << "\n";
            return false;
        }
        yyrestart(fptr);
        if(!readSource()) {
            fclose(fptr);
            return false;
        }
        fclose(fptr);
        return true;
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
}

void yyerror(const char *src, ...) {
    va_list ap;
    va_start(ap, src);
    fprintf(stderr, "Error on Line %d: ", yylineno);
    vfprintf(stderr, src, ap);
    fprintf(stderr, "\n");
    mxl::error_count ++;
}

