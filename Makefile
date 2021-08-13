# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2021/08/13 16:35:41 by iren             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBFT	= libft

MLX		= mlx_linux

HEADER	= include/cub3d.h

DIR_SOURCES	= src/

DIR_PARSE = parse/

DIR_2DMAP = 2dmap/

DIR_3DMAP	= 3dmap/

SOURCES_PARSE	=	ft_parse_all.c \
					get_next_line.c \
					get_next_line_utils.c \
					ft_parse_texture.c \
					ft_parse_color.c \
					ft_parse_nb.c \
					ft_copy_mapchar.c \
					ft_rotate_mapchar.c \
					ft_free_mapchar.c \
					ft_free_previously_malloced.c \
					ft_mirror.c \
					ft_set_tmap.c \
					ft_is_map_closed.c \
					ft_skip_spaces.c \
					ft_isspace.c \
					ft_is_player_char.c \
					ft_display_things.c

SOURCES_2DMAP	=	ft_render_rect.c \
					ft_render_background.c \
					ft_render_line.c \
					ft_map_has_wall_at.c \
					ft_cast_all_rays.c \
					ft_calculate_step.c \
					ft_calculate_intercept.c \
					ft_find_wall_hit_xy.c \
					ft_fill_ray_data.c 

SOURCES_3DMAP	=	ft_generate_walls_projection.c \
					ft_import_xpm_file.c \
					ft_walls_projection.c 

SOURCES		=	main.c \
				ft_init_tmap.c \
				ft_free_tmap.c \
				ft_mlx.c \
				ft_close.c \
				ft_mlx_hook.c \
				ft_img_pix_put.c \
				ft_refresh_img.c \
				$(addprefix $(DIR_2DMAP), $(SOURCES_2DMAP)) \
				$(addprefix $(DIR_3DMAP), $(SOURCES_3DMAP)) \
				$(addprefix $(DIR_PARSE), $(SOURCES_PARSE))


SRCS	=	$(addprefix $(DIR_SOURCES), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= -MD -g -Wall -Wextra -Werror 

RM		= rm -f

all		: $(NAME)

%.o		: %.c
		$(CC) $(CFLAGS) -Iinclude -Imlx_linux -O3 -c $< -o $@

$(NAME) : $(OBJS) $(HEADER) $(MLX) $(LIBFT)
		make -C $(MLX)
		make -C $(LIBFT)
		make bonus -C $(LIBFT)
		$(CC) -o $@ $(OBJS) -Llibft -lft -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm
	#	$(CC) -o $@ $(OBJS) mlx_linux/libmlx_Linux.a -Imlx_linux -lXext -lX11 -lm -lz

norm	:
		norminette $(SRCS)
		norminette -R CheckDefine $(HEADER)

clean	:
		$(RM) $(OBJS)
		$(RM) $(OBJS:.o=.d)
		make clean -C $(LIBFT)
		make clean -C $(MLX)

fclean	: clean
		make fclean -C $(LIBFT)
		$(RM) $(NAME)

re		: fclean all

-include $(OBJS:.o=.d)

.PHONY:	all clean fclean re
