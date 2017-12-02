CXX_FLAGS= -O2

mxltest: mxl.hpp mxl.cpp parser.y lexer.l
	bison -d parser.y
	mv parser.tab.c parser.tab.cpp
	flex lexer.l
	mv lex.yy.c lex.yy.cpp
	$(CXX) mxl.cpp -c -o mxl.o
	$(CXX) parser.tab.cpp -c -o parser.o
	$(CXX) lex.yy.cpp -c -o lex.o
	$(CXX) main.cpp -c -o main.o
	$(CXX) mxl.o parser.o lex.o main.o -o mxltest
all: mxltest


clean:
	rm -f mxltest *.o
