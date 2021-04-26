/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:14:08 by iren              #+#    #+#             */
/*   Updated: 2021/04/18 16:45:28 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_h

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include "get_next_line.h"

# define SUCCESS 1
# define FAILURE 0

///////// LIBFT FUNCTIONS
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *s);

//////// STRUCT
typedef struct	s_map
{
	int		error;
	int		res_x;
	int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sprite;
	char	*floor;
	char	*ceiling;

}				t_map;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;


typedef struct  s_img {
    void        *mlx_img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
	t_rect		*rect;
}               t_img;

typedef struct s_player
{
	int	x;
	int	y;

}				t_player;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}				t_data;


void	ft_init_map(t_map *map);
int	ft_parse_map(char *name, t_map *map);
void	ft_parse_R(char *line, t_map *map);
void	ft_parse_texture(char *line, t_map *map);
int	ft_skip_spaces(char *s, int i);
int	ft_is_space(char c);
int ft_res_length(char *res);

int	ft_mlx(t_map map);
void	ft_img_pix_put(t_img *img, int x, int y, int color);
void	ft_update(t_player *p);
int	ft_close(t_data *vars);
#endif
