CC = g++

CFLAGS = -Wall -Wextra -Werror -g -Iinc -std=c++11

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.cpp \
	   $(SRC_DIR)/Algo/FindBestMove.cpp \
	   $(SRC_DIR)/Game/Board.cpp \
	   $(SRC_DIR)/Game/CountPoints.cpp \
	   $(SRC_DIR)/Game/GettersSetters.cpp \
	   $(SRC_DIR)/Game/Init.cpp \
	   $(SRC_DIR)/Game/Player.cpp \
	   $(SRC_DIR)/Game/Tile.cpp \
	   $(SRC_DIR)/Game/Utils.cpp \
	   $(SRC_DIR)/Game/WordCheck.cpp \

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

EXEC = ScrabBot

all: ascii_art_compil $(EXEC)

ascii_art_compil:
	@echo "      _.--._  _.--._             "
	@echo ",-=.-\":;:;:;\':;:;:;\"-._         "
	@echo "\\\\\:;:;:;:;:;\:;:;:;:;:;\        "
	@echo " \\\\\:;:;:;:;:;\:;:;:;:;:;\       "
	@echo "  \\\\\:;:;:;:;:;\:;:;:;:;:;\      "
	@echo "   \\\\\:;:;:;:;:;\:;::;:;:;:\     "
	@echo "    \\\\\;:;::;:;:;\:;:;:;::;:\    "
	@echo "     \\\\\;;:;:_:--:\:_:--:_;:;\   "
	@echo "      \\\\\_.-\"      :      \"-._\  "
	@echo "       \\\`_..--\"\"--.;.--\"\"--.._=) "
	@echo "        \"\"                       "

ascii_art_decompil:

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(EXEC)

re: fclean all

.PHONY: all clean fclean re