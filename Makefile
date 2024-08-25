all: clean make++

parser.o: parser.cpp parser.hpp
	g++ -c parser.cpp -o parser.o
parser.cpp:
parser.hpp:

expressions.o: expressions.cpp expressions.hpp
	g++ -c expressions.cpp -o expressions.o
expressions.cpp:
expressions.hpp:

main.o: main.cpp
	g++ -c main.cpp -o main.o
main.cpp:

make++: parser.o expressions.o main.o
	g++ parser.o expressions.o main.o -o make++

clean:
	rm -rf *.o make++
