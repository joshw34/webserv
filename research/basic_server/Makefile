PROJECT = server

NAME = $(PROJECT)
DBG_NAME = $(PROJECT)-debug

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

SRC_FILES =	$(SRC_DIR)main.cpp \

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
DBG_OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.debug.o)

REMOVE = rm -f
REMOVE_DIR = rm -rf

CC = clang++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -I$(INC_DIR)
DBG_CFLAGS = -g


all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "Compiling/Linking"
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "Ready"

debug: $(DBG_NAME)

$(DBG_NAME): $(DBG_OBJ_FILES)
	@echo "Compiling/Linking with debug flags"
	@$(CC) $(CFLAGS) $(DBG_CFLAGS) $(DBG_OBJ_FILES) -o $(DBG_NAME)
	@echo "Debug executable ready"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.debug.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(DBG_CFLAGS) -c $< -o $@

clean:
	@echo "Removing .o files"
	@$(REMOVE_DIR) $(OBJ_DIR)

fclean:	clean
	@echo "Removing executable"
	@$(REMOVE) $(NAME) $(DBG_NAME)

re:	fclean all

.PHONY: all clean fclean re debug
