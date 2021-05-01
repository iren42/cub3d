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

I		= -I include \
		-I /usr/include \
		-I mlx_linux

HEADER	= include/cub3d.h

MLX		= mlx_linux

MLX_FLAGS	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

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
			  ft_res_length.c \
			  \
			  ft_mlx.c \
			  ft_img_pix_put.c \
			  ft_close.c \
			  ft_render_rect.c \
			ft_render_background.c \
			ft_render_line.c \
			ft_abs.c \
			ft_swap.c \
			ft_refresh_img.c \
			ft_mlx_hook.c

SRCS	= $(addprefix $(DIR_S), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= -MD

RM		= rm -f

all		: $(NAME)

%.o		: %.c
		$(CC) $(CFLAGS) -Iinclude -Imlx_linux -O3 -c $< -o $@

$(NAME) : $(OBJS) $(HEADER) $(MLX)
		make -C $(MLX)
		$(CC) -o $@ $(OBJS) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz
	#	$(CC) -o $@ $(OBJS) mlx_linux/libmlx_Linux.a -Imlx_linux -lXext -lX11 -lm -lz

norm	:
		norminette $(SRCS)
		norminette -R CheckDefine $(HEADER)

clean	:
		$(RM) $(OBJS)
		make clean -C $(MLX)

fclean	: clean
		$(RM) $(NAME)

re		: fclean all

-include $(OBJS:.o=.d)

.PHONY:	all clean fclean re
