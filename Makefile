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

LIBMLX		= MLX42
HEADERS 	= -I $(LIBMLX)/include
LIBS		= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm

CFLAGS		= -Wall -Wextra -Werror -Wunreachable-code -Ofast
CC			= cc

CFILES		= so_long.c

OFILES		= $(CFILES:.c=.o)

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OFILES)
	make -C $(LIBFTDIR)
	$(CC) $(OFILES) $(LIBFTDIR)/$(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -f $(OFILES)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	rm -f $(LIBMLX)/build/libmlx42.a

re: fclean $(NAME)

.PHONY: all clean fclean re libmlx
