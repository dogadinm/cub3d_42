NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra 
MLXFLAGS	=	-lm -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11
LIBFT = ./libft/libft.a
LIBFTDIR = ./libft
MINILIBX_PATH	=	./minilibx-linux
MINILIBX		=	$(MINILIBX_PATH)/libmlx.a
SRC = main.c raycasting.c game_loop.c read_map_file.c check_elements.c free_map.c move.c get_color.c allocate_map.c texture.c

OBJ = $(SRC:%.c=%.o)

all: ${NAME}

${NAME}: $(OBJ)
	$(MAKE) --no-print-directory -C $(MINILIBX_PATH)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(FLAGS)  $(SRC) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft
	@rm -rf $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re