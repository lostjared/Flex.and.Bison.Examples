
CXX_FLAGS= -O2

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

source/%.o: source/%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

all: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES)  -o mxltest  

flex: parser.y lexer.l
	bison -d parser.y
	mv parser.tab.c parser.tab.cpp
	flex lexer.l
	mv lex.yy.c lex.yy.cpp

clean:
	rm -f mxltest *.o


