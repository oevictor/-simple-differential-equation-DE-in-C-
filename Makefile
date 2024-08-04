# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I/usr/include/gtest -g -pthread

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/populacao.cpp $(SRC_DIR)/mutacao.cpp $(SRC_DIR)/selecao.cpp
# Object files
OBJ_FILES = $(SRC_DIR)/main.o $(SRC_DIR)/populacao.o $(SRC_DIR)/mutacao.o $(SRC_DIR)/selecao.o

# Executable name
MAIN_EXEC = $(BIN_DIR)/main

# Libraries
LIBS = -L/usr/lib -lgtest -lgtest_main

# Targets
all: $(MAIN_EXEC)

# Main application
$(MAIN_EXEC): $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LIBS) -o $(MAIN_EXEC)

# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Object file rules
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run application
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Clean up
clean:
	rm -f $(OBJ_FILES) $(BIN_DIR)/*

.PHONY: all clean run
