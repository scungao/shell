CC = g++
FLAGS = -O3
INCUDE = -I./src/
FB = -ly -ll
all: shell 
shell: main ast table converter tester power parser
	$(CC) $(FLAGS) $(FB) main.o ast.o table.o converter.o lex.yy.o parser.tab.o tester.o power.o -o shell
main: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp
power: src/power.cpp
	$(CC) $(FLAGS) -c src/power.cpp
ast: src/ast.cpp 
	$(CC) $(FLAGS) -c src/ast.cpp
table: src/table.cpp
	$(CC) $(FLAGS) -c src/table.cpp
tester: src/tester.cpp
	$(CC) $(FLAGS) -c src/tester.cpp
converter: src/converter.cpp	
	$(CC) $(FLAGS) -c src/converter.cpp
parser.tab.c parser.tab.h: src/parser.y
	bison -d src/parser.y
lex.yy.c: src/lexer.l parser.tab.h
	flex src/lexer.l
parser: lex.yy.c parser.tab.c parser.tab.h
	$(CC) $(FLAGS) -c lex.yy.c parser.tab.c
clean:
	rm -rf *.o cda


