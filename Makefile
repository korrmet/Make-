# Standard GNU Make script

all: make++

parser.o: parser.cpp parser.hpp
	g++ -c parser.cpp -o parser.o
parser.cpp:
parser.hpp:

expressions.o: expressions.cpp expressions.hpp
	g++ -c expressions.cpp -o expressions.o
expressions.cpp:
expressions.hpp:

core.o: core.cpp core.hpp
	g++ -c core.cpp -o core.o
core.cpp:
core.hpp:

main.o: main.cpp
	g++ -c main.cpp -o main.o
main.cpp:

make++: parser.o expressions.o core.o  main.o
	g++ parser.o expressions.o core.o main.o -o make++

clean:
	rm -rf *.o make++
