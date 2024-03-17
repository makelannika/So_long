# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 18:17:01 by amakela           #+#    #+#              #
#    Updated: 2024/02/22 18:20:59 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

LIBFTDIR	= libft
LIBFT		= libft.a

MLX42		= MLX42
LIBMLX42	= $(MLX42)/build/libmlx42.a
HEADERS 	= -I $(MLX42)/include
LIBS		= $(LIBFTDIR)/$(LIBFT) $(LIBMLX42) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

CFLAGS		= -Wall -Wextra -Werror
CC			= cc

CFILES		= map_utils.c		map_check_utils.c		layout_check_utils.c		\
			graphics_utils.c	movement_utils.c		cleaning_utils.c			\
			so_long.c

OFILES		= $(CFILES:.c=.o)

all: $(LIBMLX42) $(NAME)

$(LIBMLX42):
	@cmake $(MLX42) -B $(MLX42)/build && make -C $(MLX42)/build -j4

$(NAME): $(OFILES)
	make -C $(LIBFTDIR)
	$(CC) $(OFILES) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -f $(OFILES)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	rm -rf $(MLX42)/build

re: fclean all

.PHONY: all clean fclean re libmlx
