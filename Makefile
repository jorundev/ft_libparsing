# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/15 21:09:15 by hroussea          #+#    #+#              #
#    Updated: 2021/02/15 22:50:35 by hroussea         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libftparsing.a
CFLAGS = -Wall -Wextra -Werror -O3
SRCS = tokens.c match.c parsing.c utils.c funcs.c funcs2.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

%.o: %.c funcs.h parsing.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} exe

re: fclean all

exe: all
	${CC} main.c -O3 -o exe -L . -lftparsing

.PHONY: all clean fclean re exe
