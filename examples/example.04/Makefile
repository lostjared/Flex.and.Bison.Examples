
all: ast_test

ast_test: parser.y scanner.l main.cpp astsrc.cpp astheader.hpp
	bison -d parser.y
	flex scanner.l
	mv lex.yy.c lex.yy.cpp
	mv parser.tab.c parser.tab.cpp
	$(CXX) parser.tab.cpp lex.yy.cpp astsrc.cpp main.cpp -o ast_test


clean:
	rm -f ast_test
