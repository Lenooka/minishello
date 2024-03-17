# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 13:14:14 by otolmach          #+#    #+#              #
#    Updated: 2024/01/06 18:54:14 by otolmach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC				=	ft_isalpha.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strdup.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_print_c.c ft_print_number.c ft_print_p.c ft_print_precent.c ft_print_s.c ft_print_u.c  ft_print_x.c get_next_line.c get_next_line_utils.c
OBJS = $(SRC:.c=.o)

HDRS = ./

all: $(NAME)

.c.o:
	cc -Wall -Wextra -Werror -c -I $(HDRS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
		ar -rc $(NAME) $(OBJS)
		ranlib $(NAME)

clean:
		rm -f $(OBJS)
		
fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re