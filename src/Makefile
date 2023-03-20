CXX=clang++
CXXFLAGS=-I/usr/local/include -D_THREAD_SAFE -std=c++20 -g
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

snake_game: main.o snake.o
	$(CXX) main.o snake.o $(LDFLAGS) -o snake_game

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

snake.o: snake.cpp snake.hpp graphical_element.hpp
	$(CXX) $(CXXFLAGS) -c snake.cpp

all: clean snake_game

.PHONY: clean
clean:
	rm -rf *.o snake_game
