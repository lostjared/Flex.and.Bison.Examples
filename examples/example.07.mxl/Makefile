
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

%.o: %.cpp
	$(CXX) -O2 -std=c++11  -c -o $@ $<

mxltest: $(OBJ_FILES) lex.yy.o
	$(CXX) lex.yy.cc -c -o lex.yy.o
	$(CXX) $(OBJ_FILES) lex.yy.o  -o mxltest  

#install: mxltest
#	$(CXX) $(CXX_FLAGS) -shared -o libMXL.so  lex.yy.o mxl.o parser.tab.o
#	$(CXX) main.o -o mxl-shared-test -L. -lMXL 

all: mxltest

flex: parser.yy lexer.l
	bison -d parser.yy
	mv parser.tab.cc parser.tab.cpp
	flex lexer.l
	mv lex.yy.c lex.yy.cc

clean:
	rm -f mxltest *.o


