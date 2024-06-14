NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra
MLXFLAGS = -lm -L ./minilibx-linux -lmlx -lXext -lX11
LIBFT = ./libft/libft.a
LIBFTDIR = ./libft
MINILIBX_PATH = ./minilibx-linux
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(MINILIBX_PATH) -I$(LIBFTDIR) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) --no-print-directory -C $(MINILIBX_PATH)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(FLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re