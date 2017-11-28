
all: ast_test

ast_test: parser.y scanner.l main.cpp astsrc.cpp astheader.hpp
	bison -d parser.y
	flex scanner.l
	mv lex.yy.c lex.yy.cpp
	$(CXX) lex.yy.cpp -c -o lex.yy.o
	mv parser.tab.c parser.tab.cpp
	$(CXX) parser.tab.cpp -c -o parser.tab.o
	$(CXX) -std=c++11 astsrc.cpp -c -o astsrc.o
	$(CXX) -std=c++11 main.cpp -c -o main.o
	$(CXX) parser.tab.o lex.yy.o astsrc.o main.o -o ast_test
#	$(CXX) parser.tab.cpp lex.yy.cpp astsrc.cpp main.cpp -o ast_test 


clean:
	rm -f *.o ast_test
