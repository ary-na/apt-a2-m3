.default: all

all: Qwirkle

clean:
	rm -rf Qwirkle src/*.o *.dSYM

Qwirkle: src/Tile.o src/Qwirkle.o src/FileHandler.o src/Hand.o src/TileBag.o src/Node.o src/LinkedList.o src/Board.o src/Player.o src/Game.o src/Controller.o src/Validator.o src/Moves.o src/ScoreCalculator.o src/FileHandler.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

src/%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

# disable all warnings
CXXFLAGS += -w
