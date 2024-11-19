NAME = pipex
CC = cc
CCFLAGS = -Wall -Wextra -Werror
SRC =	src/pipex.c
OBJ = $(SRC:.c=.o)
LIBFT = libft.a
LIBFT_DIR = libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $^

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	rm -f $(LIBFT_DIR)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/$(LIBFT)

re: fclean all

.PHONY: all clean fclean re 