
all: cpp_test

cpp_test: scanner.l
	flex scanner.l
	mv lex.yy.c lex.yy.cpp
	$(CXX) lex.yy.cpp -o cpp_test

clean:
	rm -f cpp_test
