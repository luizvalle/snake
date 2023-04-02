CXX=clang++
CXXFLAGS=-I/usr/local/include -D_THREAD_SAFE -std=c++20 -O2
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

snake_game: main.o system.o command.o input_handler.o
	$(CXX) main.o system.o command.o input_handler.o $(LDFLAGS) -o snake_game

main.o: main.cpp entity.hpp component.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

system.o: system.cpp system.hpp
	$(CXX) $(CXXFLAGS) -c system.cpp

command.o: command.cpp command.hpp
	$(CXX) $(CXXFLAGS) -c command.cpp

input_handler.o: input_handler.cpp input_handler.hpp
	$(CXX) $(CXXFLAGS) -c input_handler.cpp

all: clean snake_game

.PHONY: clean
clean:
	rm -rf *.o snake_game
