# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/08/15 15:07:54 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = 	srcs/main.c	\
		srcs/read_map/read_map.c	\
		srcs/read_map/check_map.c	\
		srcs/read_map/check_map_utils.c \
		srcs/read_map/roue_libre.c \
		srcs/roue_libre2.c

OBJS = ${SRCS:.c=.o}

INCLUDES = headers/cub3d.h

CC = gcc #-fsanitize=address,leak
RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: lib ${NAME}

# linux ${CC} ${OBJS} -Llibft -lft -Lmlx/mlx_linux -lmlx -lXext -lX11 -o $(NAME)
# mac   ${CC} ${OBJS} -Llibft -lft -Lmlx/mlx_mac -lmlx -framework OpenGL -framework Appkit -o $(NAME)
$(NAME): ${OBJS}
	${CC} ${OBJS} -Llibft -lft -Lmlx/mlx_mac -lmlx -framework OpenGL -framework Appkit -o $(NAME)

%.o: %.c ${INCLUDES} Makefile
	${CC} ${FLAGS} -Imlx -Ift -c $< -o $@

clean:
	${RM} ${OBJS}
	make clean -C mlx/mlx_mac
	make clean -C libft

fclean:	clean
	${RM} ${NAME} ${EXECUTABLE}

lib:
	make -C mlx/mlx_mac
	make -C libft

re:	fclean all
         
.PHONY: all clean fclean re 