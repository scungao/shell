CC = g++
FLAGS = -O3 
INCUDE = -I/usr/local/include/boost/
all: cda 
cda: main ast table parser converter tester power
	$(CC) $(FLAGS) main.o ast.o table.o parser.o converter.o tester.o power.o -o cda
main: main.cpp
	$(CC) $(FLAGS) -c main.cpp
power: power.cpp
	$(CC) $(FLAGS) -c power.cpp
ast: ast.cpp 
	$(CC) $(FLAGS) -c ast.cpp
table: table.cpp
	$(CC) $(FLAGS) -c table.cpp
parser: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp
tester: tester.cpp
	$(CC) $(FLAGS) -c tester.cpp
converter: converter.cpp	
	$(CC) $(FLAGS) -c converter.cpp
clean:
	rm -rf *.o cda
