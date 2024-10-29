CC = g++

CFLAGS = -Wall -Wextra -Werror -g -Iinc -std=c++11

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.cpp \
	   $(SRC_DIR)/Algo/FindBestMove.cpp \
	   $(SRC_DIR)/Game/Play.cpp \
	   $(SRC_DIR)/Game/CountPoints.cpp \
	   $(SRC_DIR)/Game/GettersSetters.cpp \
	   $(SRC_DIR)/Game/Init.cpp \
	   $(SRC_DIR)/Game/Player.cpp \
	   $(SRC_DIR)/Game/Tile.cpp \
	   $(SRC_DIR)/Game/Utils.cpp \
	   $(SRC_DIR)/Game/WordCheck.cpp \

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

EXEC = ScrabBot

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

all: compiling_message $(EXEC) compiled_message

compiling_message:
	@clear
	@echo "$(GREEN)\nCompiling ScrabBot...$(RESET)"

compiled_message:
	@echo "$(GREEN)\nScrabBot compiled!\n$(RESET)"

cleaning_message:
	@clear
	@echo "\nCleaning ScrabBot...$(RESET)" 

cleaned_message:
	@echo "$(RED)\nScrabBot cleaned.$(RESET)"
	@echo "$(RED)Goodbye!\n"

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean: cleaning_message
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory cleaned_message


fclean: clean
	@rm -rf $(EXEC)

re: fclean all

.PHONY: all clean fclean re