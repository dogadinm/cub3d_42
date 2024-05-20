# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 12:14:44 by mdogadin          #+#    #+#              #
#    Updated: 2023/10/25 13:01:38 by mdogadin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar

SRC = ft_atoi.c ft_memchr.c ft_split.c ft_strncmp.c ft_bzero.c \
	ft_memcmp.c ft_strchr.c ft_strnstr.c ft_calloc.c ft_memcpy.c \
	ft_strdup.c ft_strrchr.c ft_memmove.c ft_striteri.c ft_isalnum.c\
	ft_strtrim.c ft_isalpha.c ft_memset.c ft_strjoin.c ft_substr.c \
	ft_isascii.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c ft_isdigit.c \
	ft_putendl_fd.c ft_strlcpy.c ft_toupper.c ft_isprint.c ft_putnbr_fd.c \
	ft_strlen.c ft_itoa.c ft_putstr_fd.c ft_strmapi.c ft_printf.c ft_putnbr.c \
	ft_putnbr_hexad.c ft_putnbr_unsigned.c ft_putptr.c ft_putstr.c get_next_line.c \
	get_next_line_utils.c \
	

SRCBONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)

$(NAME): $(OBJ)
	$(AR) rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

bonus: $(OBJ) $(OBJBONUS)
	$(AR) rc $(NAME) $(OBJ) $(OBJBONUS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJBONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
