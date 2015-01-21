CC = g++
FLAGS = 
INCUDE = -I/usr/local/include/boost/
all: cda 
cda: main ast table parser converter tester
	$(CC) $(FLAGS) main.o ast.o table.o parser.o converter.o tester.o -o cda
main: main.cpp
	$(CC) $(FLAGS) -c main.cpp
ast: ast.cpp 
	$(CC) $(FLAGS) -c ast.cpp
table: table.cpp
	$(CC) $(FLAGS) -c table.cpp
parser: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp
converter: converter.cpp	
	$(CC) $(FLAGS) -c converter.cpp
tester: tester.cpp
	$(CC) $(FLAGS) -c tester.cpp
clean:
	rm -rf *.o cda
