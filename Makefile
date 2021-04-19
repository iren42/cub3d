# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2021/04/18 15:34:28 by iren             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

DIR_H	= include

HEADER	= cub3d.h

DIR_S	= srcs/

SOURCES		= main.c \
			  ft_parse_map.c \
			  ft_strnstr.c \
			  ft_strncmp.c \
			  get_next_line.c \
			  get_next_line_utils.c \
			  ft_atoi.c \
			  ft_init_map.c \
			  ft_is_space.c \
			  ft_skip_spaces.c \
			  ft_parse_R.c \
			  ft_parse_texture.c \
			  ft_res_length.c

SRCS	= $(addprefix $(DIR_S), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= 

RM		= rm -f

all		: $(NAME)

.c.o	:
		$(CC) -I$(DIR_H) $(CFLAGS) -g -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS) $(DIR_H)/$(HEADER)
		gcc -o $(NAME) $(OBJS)

norm	:
		norminette $(SRCS)
		norminette -R CheckDefine $(DIR_H)/$(HEADER)

clean	:
		$(RM) $(OBJS)

fclean	: clean
		$(RM) $(NAME)

re		: fclean all

.PHONY:	all clean fclean re
