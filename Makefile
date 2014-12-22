CC = g++
FLAGS = -c
all: cal 
cal: main ast symbol	
	$(CC) main.o ast.o symbol.o -o cal
main: main.cpp
	$(CC) $(FLAGS) main.cpp
ast: ast.cpp 
	$(CC) $(FLAGS) ast.cpp
symbol: symbol.cpp 
	$(CC) $(FLAGS) symbol.cpp
clean:
	rm -rf *.o cal
