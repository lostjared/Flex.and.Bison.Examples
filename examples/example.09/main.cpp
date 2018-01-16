#define DEBUG_MODE
#include<iostream>
#include"syntax-tree.hpp"


extern int yyparse();
extern void yyrestart(FILE *);

int main(int argc, char **argv) {
    try {
        if(argc == 1) {
            yyparse();
#ifdef DEBUG_MODE
            ast::sym_table.printTable();
#endif
        } else if(argc == 2) {
            FILE *fptr = fopen(argv[1], "r");
            if(!fptr) {
                std::cerr << "Error file not found: " << argv[1] << "\n";
                exit(EXIT_FAILURE);
            }
            yyrestart(fptr);
            yyparse();
            fclose(fptr);
        } else {
            std::cerr << "Argument requires file..\n";
        }
    } catch(ast::SymbolException &se) {
        std::cerr << "Error: " << se.get() << "\n";
        exit(EXIT_FAILURE);
    } catch(ast::DivideByZero) {
        std::cerr << "Error divide by Zero Exception...\n";
        exit(EXIT_FAILURE);
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
