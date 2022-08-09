# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/08/09 15:50:18 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = 	srcs/main.c

OBJS = ${SRCS:.c=.o}

INCLUDES = headers/cub3d.h

CC = gcc #-fsanitize=address
RM = rm -f

FLAGS = -Wall -Wextra -Werror

all: lib ${NAME}

# linux ${CC} ${OBJS} -Lmlx/mlx_linux -lmlx -lXext -lX11 -o $(NAME)
# mac   ${CC} ${OBJS} -Lmlx/mlx_mac -lmlx -framework OpenGL -framework Appkit -o $(NAME)
$(NAME): ${OBJS}
	${CC} ${OBJS} -Lmlx/mlx_mac -lmlx -framework OpenGL -framework Appkit -o $(NAME)

%.o: %.c ${INCLUDES} Makefile
	${CC} ${FLAGS} -Imlx -c $< -o $@

clean:
	${RM} ${OBJS}
	make clean -C mlx/mlx_mac

fclean:	clean
	${RM} ${NAME} ${EXECUTABLE}

lib:
	make -C mlx/mlx_mac

re:	fclean all
         
.PHONY: all clean fclean re 