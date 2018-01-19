CXX_FLAGS=-std=c++11
LDFLAGS=
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
OUTPUT_NAME=cc-test

%.o: %.cpp tree.hpp table.hpp syntax-tree.hpp intcode.hpp symbol.hpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<
  

all: $(OBJ_FILES)
	$(CXX) -std=c++11 parser.tab.cc -c -o parser.tab.o
	$(CXX) -Wno-deprecated-register -std=c++11 lex.yy.cc -c -o lex.yy.o
	$(CXX) $(OBJ_FILES) parser.tab.o lex.yy.o  -o $(OUTPUT_NAME)  $(LDFLAGS)

flex:
	bison -d parser.yy
	flex lexer.l
	mv lex.yy.c lex.yy.cc

dclean:
	make -f Makefile.debug clean

debug:
	make -f Makefile.debug

install: all
	cp $(OUTPUT_NAME) /usr/local/bin

clean:
	rm -f $(OUTPUT_NAME) *.o 

