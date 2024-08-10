# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 13:59:06 by gwagner           #+#    #+#              #
#    Updated: 2024/08/10 17:46:48 by gwagner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS      = so_long.c map_parsing.c map_parsing2.c get_next_line.c utils.c list_util01.c list_util02.c mov.c floodcheck.c
CC        = cc
OBJS      = $(SRCS:.c=.o)
CFLAGS    = -Wall -Wextra -Werror -g
MLX_DIR   = minilibx-linux/
MLX 	  = ${MLX_DIR}libmlx.a -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXrender -lXfixes -lm
NAME      = so_long
MLX_FLAGS = -L/usr/X11/lib

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -sC ./printf
	$(MAKE) -sC $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(SRCS) $(MLX) ./printf/libftprintf.a
	# firefox https://shattereddisk.github.io/rickroll/rickroll.mp4

clean:
	$(MAKE) clean -sC ./printf
	$(MAKE) clean -sC $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -sC ./printf
	$(MAKE) clean -sC $(MLX_DIR)
	rm -f $(MLX_DIR)libmlx.a
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re