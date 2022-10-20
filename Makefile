# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 08:34:54 by rbony             #+#    #+#              #
#    Updated: 2022/10/20 11:04:05 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

NAME_BONUS = cub3d_bonus

SRCS_GLOBAL = 	srcs/main.c	\
		srcs/read_map/read_map.c	\
		srcs/read_map/check_map.c	\
		srcs/read_map/check_map_utils.c \
		srcs/read_map/error.c	\
		srcs/read_map/parse_textures.c \
		srcs/raycasting/raycasting.c \
		srcs/raycasting/raycasting_utils.c \
		srcs/raycasting/dda.c \
		srcs/raycasting/vertical_rays.c	\
		srcs/raycasting/horizontal_rays.c	\
		srcs/game/texture.c	\
		srcs/game/rotate.c \
		srcs/game/events.c

SRCS_MANDATORY = srcs/game/movements.c

SRCS_BONUS = srcs/game/movements_bonus.c

OBJS_GLOBAL = ${SRCS_GLOBAL:.c=.o}
OBJS_MANDATORY = ${SRCS_MANDATORY:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

INCLUDES = headers/cub3d.h

CC = gcc #-fsanitize=address
RM = rm -f

FLAGS = -Wall -Wextra -Werror -O3

all: lib ${NAME}

bonus: lib ${NAME_BONUS}

$(NAME): ${OBJS_GLOBAL} ${OBJS_MANDATORY}
	${CC} ${OBJS_GLOBAL} ${OBJS_MANDATORY} -Llibft -lft -Lmlx/mlx_mac -lmlx -framework OpenGL -framework Appkit -o $(NAME)

${NAME_BONUS}: ${OBJS_GLOBAL} ${OBJS_BONUS}
	${CC} ${OBJS_GLOBAL} ${OBJS_BONUS} -Llibft -lft -Lmlx/mlx_mac -lmlx -framework OpenGL -framework Appkit -o $(NAME_BONUS)
	
%.o: %.c ${INCLUDES} Makefile
	${CC} ${FLAGS} -Imlx -Ift -c $< -o $@

clean:
	${RM} ${OBJS_GLOBAL} ${OBJS_MANDATORY} ${OBJS_BONUS}
	make clean -C mlx/mlx_mac
	make clean -C libft

fclean:	clean
	${RM} ${NAME} ${NAME_BONUS}
	make fclean -C libft

lib:
	make -C mlx/mlx_mac
	make -C libft

re:	fclean all
         
.PHONY: all clean fclean re 