# program: objects
# 	g++ main.o matrix.o -o program

# objects: 
# 	g++ -c ./src/matrix.cpp ./main.cpp 

# clean:
# 	rm main.o matrix.o program 

# (old code above)



# compiler 
CXX = g++

# Compiler flags
# CFLAGS = -Wall -Wextra -std=c++17 -D_POSIX_C_SOURCE=199309L
CXXFLAGS = -Wall -Wextra -std=c++17 

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Executable
EXEC = $(BIN_DIR)/run

# Main file
MAIN = $(SRC_DIR)/main.cpp

# default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Compile source files to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(BIN_DIR)/*.o $(EXEC)

# Phony targets
.PHONY: all clean

