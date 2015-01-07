CC = g++
FLAGS = -c
INCUDE = -I/usr/local/include/boost/
all: cal 
cal: main ast dictionary parser
	$(CC) main.o ast.o dictionary.o parser.o -o cal
main: main.cpp
	$(CC) $(FLAGS) main.cpp
ast: ast.cpp 
	$(CC) $(FLAGS) ast.cpp
dictionary: dictionary.cpp
	$(CC) $(FLAGS) dictionary.cpp
parser: parser.cpp
	$(CC) $(FLAGS) parser.cpp
clean:
	rm -rf *.o cal
