#include"table.hpp"

extern int yyparse();
extern void yyrestart(FILE *);

int main(int argc, char **argv) {
    if(argc == 2) {
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
	return 0;
}
