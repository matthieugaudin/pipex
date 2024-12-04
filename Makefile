NAME = pipex
CC = cc
CCFLAGS = -Wall -Wextra -Werror
SRC =	src/main.c src/ft_clean.c src/ft_exec.c src/ft_init_pipex.c src/ft_parse_args.c \
		src/ft_parse_paths.c src/ft_utils.c
OBJ = $(SRC:.c=.o)
LIBFT = libft.a
LIBFT_DIR = libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $^

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re 