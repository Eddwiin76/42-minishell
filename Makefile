# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 10:05:58 by tpierre           #+#    #+#              #
#    Updated: 2020/12/18 11:14:01 by tpierre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS		=	srcs/minishell.c \
				srcs/gnl.c \
				srcs/exit.c \
				srcs/env.c \
				srcs/prompt.c \
				srcs/signal.c \
				srcs/parse.c \
				srcs/echo.c \
				srcs/cd.c \
				srcs/export.c \
				srcs/export_bis.c \
				srcs/unset.c \
				srcs/utility.c \
				srcs/utility2.c \
				srcs/utility3.c \
				srcs/pwd.c \
				srcs/sort_export.c \
				srcs/quit.c \
				srcs/dollar_sign.c \
				srcs/checker.c \
				srcs/utility_encoder.c \
				srcs/utility_unset.c \
				srcs/decoder.c \
				srcs/process.c \
				srcs/pipe.c \
				srcs/error.c \
				srcs/multiple_split.c \
				srcs/fork.c \
				srcs/free.c \


OBJS		= ${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

LIBFT_FLAGS	= -Llibft -lft

INCLUDES	= -I libft

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

$(NAME): 	${OBJS}
			make -C libft
			${CC} ${OBJS} ${LIBFT_FLAGS} -o ${NAME}
clean:
			make -C libft clean
			${RM} ${OBJS}


fclean:		clean
			rm -f libft/libft.a
			${RM} ${NAME}

re:			fclean
			make all

.PHONY:		all clean fclean re
