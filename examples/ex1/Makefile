
all: test_flex

test_flex: scan.l parse.y
	bison -d parse.y
	flex scan.l
	gcc lex.yy.c parse.tab.c -o test_flex 
clean:
	rm -f test_flex
