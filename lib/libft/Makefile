# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 17:06:33 by olmohame          #+#    #+#              #
#    Updated: 2024/07/06 12:02:27 by olmohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a

SRCS    = ft_isalpha.c ft_isdigit.c    ft_isalnum.c ft_isascii.c ft_isprint.c \
        ft_strlen.c    ft_memset.c    ft_bzero.c    ft_memcpy.c    ft_memmove.c \
        ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c    \
        ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
        ft_calloc.c ft_strdup.c    ft_substr.c    ft_strjoin.c ft_strtrim.c ft_split.c \
        ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c    \
        ft_putendl_fd.c    ft_putnbr_fd.c  get_next_line_utils.c  get_next_line.c \
        ft_strcmp.c ft_free_contents.c

OBJS    = $(SRCS:.c=.o)

CC    = cc

CFLAGS   = -Wextra -Wall -Werror

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@ar -crs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean:    clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
