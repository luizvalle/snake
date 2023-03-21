CXX=clang++
CXXFLAGS=-I/usr/local/include -D_THREAD_SAFE -std=c++20 -O2
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

snake_game: main.o snake.o window.o
	$(CXX) main.o snake.o window.o $(LDFLAGS) -o snake_game

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

snake.o: snake.cpp snake.hpp sprite.hpp
	$(CXX) $(CXXFLAGS) -c snake.cpp

window.o: window.cpp window.hpp
	$(CXX) $(CXXFLAGS) -c window.cpp

all: clean snake_game

.PHONY: clean
clean:
	rm -rf *.o snake_game
