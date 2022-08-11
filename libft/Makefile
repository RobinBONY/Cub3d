# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 09:27:22 by rbony             #+#    #+#              #
#    Updated: 2022/08/11 11:55:42 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_calloc.c 		\
		ft_isascii.c 	\
		ft_itoa.c 		\
		ft_memcmp.c 	\
		ft_memset.c 	\
		ft_putnbr_fd.c 	\
		ft_striteri.c 	\
		ft_strlcat.c 	\
		ft_strmapi.c 	\
		ft_strrchr.c 	\
		ft_substr.c 	\
		ft_toupper.c 	\
		ft_atoi.c 		\
		ft_isalnum.c 	\
		ft_isdigit.c 	\
		ft_memcpy.c 	\
		ft_putchar_fd.c \
		ft_putstr_fd.c 	\
		ft_strchr.c 	\
		ft_strjoin.c 	\
		ft_strlen.c 	\
		ft_strcmp.c 	\
		ft_strncmp.c 	\
		ft_strtrim.c 	\
		ft_bzero.c 		\
		ft_isalpha.c 	\
		ft_isprint.c 	\
		ft_memchr.c 	\
		ft_memmove.c 	\
		ft_putendl_fd.c \
		ft_split.c 		\
		ft_strdup.c 	\
		ft_strlcpy.c 	\
		ft_strstr.c 	\
		ft_strnstr.c 	\
		ft_tolower.c 	\
		ft_lstnew.c 	\
		ft_lstadd_front.c 	\
		ft_lstsize.c 		\
		ft_lstlast.c 		\
		ft_lstadd_back.c 	\
		ft_lstclear.c 		\
		get_next_line.c		\
		get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

INCLUDES = libft.h

CC = gcc
RM = rm -f

FLAGS = -Wall -Wextra -Werror

%.o : %.c ${INCLUDES}
	${CC} ${FLAGS} -I includes -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} 
	ar rcs ${NAME} ${OBJS} 

all: ${NAME}

clean:
	${RM} ${OBJS}
	${RM} ${OBJS_BONUS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all
         
.PHONY: all clean fclean re bonus