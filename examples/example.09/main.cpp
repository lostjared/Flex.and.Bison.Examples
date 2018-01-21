/*
 
 GNU flex & bison test program
 created by Jared Bruni
 http://github.com/lostjared
 
 */
#include<iostream>
#include"syntax-tree.hpp"


extern int yyparse();
extern void yyrestart(FILE *);

int main(int argc, char **argv) {
    try {
        if(argc == 1) {
            yyparse();
#ifdef DEBUG_INFO
            ast::sym_table.printTable();
#endif
        } else if(argc == 2) {
            FILE *fptr = fopen(argv[1], "r");
            if(!fptr) {
                std::cerr << "Error file could not be opened: " << argv[1] << "\n";
                exit(EXIT_FAILURE);
            }
            yyrestart(fptr);
            yyparse();
            fclose(fptr);
#ifdef DEBUG_INFO
            ast::sym_table.printTable();
#endif
        } else {
            std::cerr << "Argument requires file..\n";
        }
    } 
    catch(std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch(...) {
        std::cerr << "Error: Unnown Exception...\n";
        exit(EXIT_FAILURE);
    }
	return EXIT_SUCCESS;
}
