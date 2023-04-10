# Directories
SDL_HEADERS_DIR = /usr/local/include -D_THREAD_SAFE
SDL_LIB_DIR = /usr/local/lib
BIN_DIR = ../bin

# Files
OBJS = $(BIN_DIR)/main.o $(BIN_DIR)/game.o $(BIN_DIR)/command.o $(BIN_DIR)/entity_manager.o $(BIN_DIR)/graphics.o $(BIN_DIR)/input_handler.o $(BIN_DIR)/main.o $(BIN_DIR)/system.o
EXECUTABLE = $(BIN_DIR)/snake_game

# Compiler and flags
CXX=clang++
CXXFLAGS=-I$(SDL_HEADERS_DIR) -std=c++20
LDFLAGS=-L$(SDL_LIB_DIR) -lSDL2

# Targets
all: clean $(EXECUTABLE)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/game.o: game.cpp game.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/command.o: command.cpp command.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/entity_manager.o: entity_manager.cpp entity_manager.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/graphics.o: graphics.cpp graphics.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/input_handler.o: input_handler.cpp input_handler.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/main.o: main.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/system.o: system.cpp system.hpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*

.PHONY: all clean