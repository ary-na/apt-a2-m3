.default: all

all: qwirkle

clean:
	rm -rf qwirkle src/*.o *.dSYM

qwirkle: src/Tile.o src/Node.o src/LinkedList.o src/qwirkle.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

src/%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^