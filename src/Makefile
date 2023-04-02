CXX=clang++
CXXFLAGS=-I/usr/local/include -D_THREAD_SAFE -std=c++20 -O2
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

snake_game: main.o system.o
	$(CXX) main.o system.o $(LDFLAGS) -o snake_game

main.o: main.cpp entity.hpp component.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

system.o: system.cpp system.hpp
	$(CXX) $(CXXFLAGS) -c system.cpp

all: clean snake_game

.PHONY: clean
clean:
	rm -rf *.o snake_game
