NAME = ft_malcom
HEADER = ./inc/ft_malcom.h
INC = ./inc
IFLAGS = -I$(INC)

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD

SRC_PATH = ./src
OBJ_PATH = $(SRC_PATH)/obj
LIB_PATH = ./inc/libft
LIB_LINK= -L$(LIB_PATH) -lft

SRC_NAMES = main.c parser.c error.c ip.c memory.c
OBJ_NAMES = $(SRC_NAMES:.c=.o)
SRCS = $(addprefix $(SRC_PATH)/, $(SRC_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/, $(OBJ_NAMES))
DEPS = $(OBJS:.o=.d)


all: $(NAME)
	@echo "ft_malcom build succesfully!\n"

$(OBJ_PATH):
	@mkdir $@
	@echo "Building ft_malcom sources:\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile $(OBJ_PATH)
	@printf "Compiling ... $<\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

libft:
	@echo "\nBuilding Libft now...\n"
	@make -C $(LIB_PATH) --no-print-directory
	
$(NAME): $(OBJS) libft
	@echo "\nBuilding $(NAME)"
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LIB_LINK)
	@echo "Done\n"

clean:
	@rm -rf $(OBJ_PATH) 
	@make -C $(LIB_PATH) fclean --no-print-directory

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean libft re

