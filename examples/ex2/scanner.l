
%option noyywrap

%{

int lines = 0, total_lines = 0;

%}

%%

\n { lines++; }
. { }
%%


int main(int argc, char **argv) {

	if(argc > 1) {
		for(unsigned int i = 1; i < argc; ++i) {
			FILE *fptr = fopen(argv[i], "r");
			yyrestart(fptr);
			while(yylex() != 0) {}
			printf("%s file has %d lines.\n", argv[i], lines);
			total_lines += lines;
			lines = 0;
			fclose(fptr);
	
		}
	} else {

		while( yylex() != 0) {}
		total_lines += lines;
		lines = 0;
	}

	printf("Total Lines: %d\n", total_lines);
	return 0;
}


