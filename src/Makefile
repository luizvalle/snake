CXX=clang++
CXXFLAGS=-I/usr/local/include -D_THREAD_SAFE -std=c++20 -O2
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image

snake_game: main.o sprite.o snake.o apple.o window.o controller.o
	$(CXX) main.o sprite.o snake.o apple.o window.o controller.o $(LDFLAGS) -o snake_game

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

sprite.o: sprite.cpp sprite.hpp
	$(CXX) $(CXXFLAGS) -c sprite.cpp

snake.o: snake.cpp snake.hpp sprite.hpp
	$(CXX) $(CXXFLAGS) -c snake.cpp

apple.o: apple.cpp apple.hpp sprite.hpp
	$(CXX) $(CXXFLAGS) -c apple.cpp

window.o: window.cpp window.hpp
	$(CXX) $(CXXFLAGS) -c window.cpp

controller.o: controller.cpp controller.hpp
	$(CXX) $(CXXFLAGS) -c controller.cpp

all: clean snake_game

.PHONY: clean
clean:
	rm -rf *.o snake_game
