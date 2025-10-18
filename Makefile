NAME = pipex
CC = cc
CCFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
LIBFT_DIR = libft

SRC =	src/ft_clean.c  src/ft_create_pipes.c  src/ft_exec.c  src/ft_init_pipex.c  src/ft_parse_args.c  \
		src/ft_parse_paths.c  src/get_next_line.c  src/main.c  src/utils.c  src/utils_1.c

OBJ = $(SRC:.c=.o)


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