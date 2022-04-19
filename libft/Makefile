# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 09:33:37 by tpierre           #+#    #+#              #
#    Updated: 2020/11/06 14:33:20 by tpierre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= libft.a

OBJS			= $(SRC:.c=.o)

OBJS_BONUS		= $(SRC_BONUS:.c=.o)

CC				= gcc

AR				= ar rc

CFLAGS			= -Wall -Wextra -Werror

RM				= rm -f

SRC				= ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memcmp.c\
					ft_strlen.c ft_strnlen.c ft_isalpha.c ft_isdigit.c ft_isalldigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c\
					ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
					ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
					ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcat.c\
					ft_realloc.c ft_strcpy.c ft_tabdel.c ft_tabsize.c ft_strcountchar.c ft_strdelchar.c\
					ft_strcmp.c ft_tabmaxlen.c ft_memccpy.c ft_memchr.c


SRC_BONUS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

INCLUDE			= ./

HEADER			= $(INCLUDE)libft.h $(INCLUDE)get_next_line.h

all:			$(NAME)

$(NAME):		$(OBJS)
				$(AR) $(NAME) $(OBJS)

bonus:			$(NAME) $(OBJS_BONUS)
				$(AR) $(NAME) $(OBJS_BONUS)

%.o: %.c		$(HEADER)
				$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re
