# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g -Iinc -std=c++11

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = main.cpp \
	   $(SRC_DIR)/Algo/FindBestMove.cpp \
	   $(SRC_DIR)/Game/Board.cpp \
	   $(SRC_DIR)/Game/GettersSetters.cpp \
	   $(SRC_DIR)/Game/Logic.cpp \
	   $(SRC_DIR)/Game/Utils.cpp \
	   $(SRC_DIR)/Game/Tile.cpp \

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
EXEC = ScrabBot

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR)

# Full clean, including any other generated files
fclean: clean
	rm -rf $(EXEC)

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re