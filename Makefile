NAME = pipex
CC = cc
CCFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
LIBFT_DIR = libft

SRC =	src/main.c src/ft_clean.c src/ft_exec.c src/ft_init_pipex.c src/ft_parse_args.c \
		src/ft_parse_paths.c src/utils.c src/utils_1.c

SRC_BONUS = src_bonus/main_bonus.c src_bonus/utils_bonus.c src_bonus/utils_1_bonus.c \
			src_bonus/ft_parse_paths_bonus.c src_bonus/ft_parse_args_bonus.c \
			src_bonus/ft_init_pipex_bonus.c src_bonus/ft_exec_bonus.c \
			src_bonus/ft_create_pipes_bonus.c src_bonus/ft_clean_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)


all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

bonus: $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CCFLAGS) $(OBJ_BONUS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $^

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re 