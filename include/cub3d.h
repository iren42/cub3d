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
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"

# define SUCCESS 1
# define FAILURE 0

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x000000


#define PI 3.14159265
#define TWO_PI 6.28318530

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13 // should be parsed from fd map
# define MAP_NUM_COLS 20 // same

# define MINIMAP_SCALE_FACTOR 1.0

#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)

# define FOV_ANGLE (60 * PI / 180)

# define NUM_RAYS WINDOW_WIDTH


extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

///////// LIBFT FUNCTIONS
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *s);

//////// STRUCT
typedef struct	s_rect
{
	int	x;
	int y;
	int width;
	int height;
	int	color;
}		t_rect;

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


typedef struct s_player
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		cam_dir; // -1 for left, +1 for right ; touches fleches droite gauche
	int		turn_dir; // -1 for left, +1 for right ; touches a, d
	int		walk_dir; // -1 for back, +1 for front ; touches w, s
	float	rotation_angle; // settings: determines how fast the player rotates
	float	walk_speed;	// settings
	float	turn_speed;	// settings
}				t_player;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}			t_ray;




typedef struct  s_img {
    void        *mlx_img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
	t_player	player;
	t_ray		*rays;
	t_map		*map; // to save the unchanging minimap here
}               t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}				t_data;

//////// MAP PARSING FUNCTIONS
void	ft_init_map(t_map *map);
int	ft_parse_map(char *name, t_map *map);
void	ft_parse_R(char *line, t_map *map);
void	ft_parse_texture(char *line, t_map *map);
int	ft_skip_spaces(char *s, int i);
int	ft_is_space(char c);
int ft_res_length(char *res);
void	ft_free_map(t_map *map);

int	ft_mlx(t_map map);
void	ft_img_pix_put(t_img *img, int x, int y, int color);
int	ft_close(t_data *data);
//////// MLX 2D MAP FUNCTIONS
void	ft_update(t_player *p);
void	ft_render_background(t_img *img, int color);
int	ft_render_rect(t_img *img, t_rect rect);
int	ft_render_line(t_img *img, int x1, int y1, int x2, int y2);
//int	ft_abs(float n);
//void	ft_swap(float *a, float *b);
void	ft_refresh_img(t_data *data);
void	ft_mlx_hook(t_data *data);
int		ft_map_has_wall_at(float x, float y);

////// MLX 3D MAP
void	ft_cast_all_rays(t_data *data, t_ray *rays);

#endif
