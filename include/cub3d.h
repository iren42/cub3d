/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:14:08 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 09:15:34 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_h

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

# define SUCCESS 1
# define FAILURE -1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define BLACK_PIXEL 0x000000

#define PI 3.14159265
#define TWO_PI 6.28318530

# define TILE_SIZE 32
# define MINIMAP_SCALE_FACTOR 0.5

# define FOV_ANGLE (60 * PI / 180)

//extern const char map[MAP_NUM_ROWS][MAP_NUM_COLS];

///////// LIBFT FUNCTIONS
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *s);

//////// STRUCT
typedef struct	s_var_cast_ray
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	int		found_hor_wall_hit;
	float	hor_wall_hit_x;
	float	hor_wall_hit_y;
	int		hor_wall_content;

	int		found_ver_wall_hit;
	float	ver_wall_hit_x;
	float	ver_wall_hit_y;
	int		ver_wall_content;
}				t_var_cast_ray;

typedef struct	s_var_spread_b
{
	int		rows;
	int		cols;
}				t_var_spread_b;


typedef struct	s_var_generate_walls_proj
{
	float		player_rotation_angle;
	float		ray_angle;
	float		ray_distance;
	float		distance_proj_plane;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			wall_strip_height;
}				t_var_generate_walls_proj;


typedef struct	s_rect
{
	int	x;
	int y;
	int width;
	int height;
	int	color;
}		t_rect;

enum e_tex{No, So, We, Ea, Sp};


typedef struct s_player
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		cam_dir; // purpose???
	int		turn_dir; // -1 for left, +1 for right ; touches left and right
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
	int		is_ray_facing_down;
	int		is_ray_facing_right;
	int		wall_hit_content;
}			t_ray;

typedef struct	s_map
{
	int		error;
	int		player_x;
	int		player_y;
	char	**map; // the actual 2d map
	char	**texture; // no, so, we, ea, sp
	int		floor;
	int		ceiling;
	int		rows; // nb of rows
	int		cols; // nb of cols
}				t_map;

typedef struct  s_img {
    void        *mlx_img;
	int			width;
	int			height;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
	t_player	player;
	t_ray		*rays;
	t_map		*tmap;
}               t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_img	*tex; // array of tex samples
}				t_data;

//////// MAP PARSING FUNCTIONS
void	ft_init_tmap(t_map *map);
int		ft_parse_all(char *name, t_map *map);
void	ft_parse_texture(char *line, t_map *map);
void	ft_parse_color(char *line, t_map *map);
int		ft_parse_nb(char *line, unsigned int *i, char c);
int		ft_skip_spaces(char *s, int i);
void	ft_free_tmap(t_map *map);
int		ft_isspace(char c);

int		ft_mlx(t_map *map);
void	ft_img_pix_put(t_img *img, int x, int y, int color);
int		ft_close(t_data *data);
char	**ft_copy_mapchar(char **map, int nb_rows, int nb_cols);
char	**ft_rotate_mapchar(char **map, int rows, int cols);
void	ft_free_mapchar(char **map);
void	ft_free_previously_malloced(char **tab, int i);
char	**ft_mirror(char **map, int rows, int cols);
int	ft_set_tmap(int fd, t_map *map);
int	ft_is_map_closed(t_map *map, int px, int py);

//////// MLX 2D MAP FUNCTIONS
void	ft_update(t_player *p);
void	ft_render_background(t_data *data, int color);
int	ft_render_rect(t_img *img, t_rect rect);
int	ft_render_line(t_img *img, int x1, int y1, int x2, int y2);
void	ft_refresh_img(t_data *data);
void	ft_mlx_hook(t_data *data);
int		ft_map_has_wall_at(t_data *data, float x, float y);

////// MLX 3D MAP
void	ft_cast_all_rays(t_data *data, t_player player, t_ray *rays);
void	ft_calculate_hor_step(float *xstep, float *ystep, t_ray ray, float ray_angle);
void	ft_calculate_ver_step(float *xstep, float *ystep, t_ray ray, float ray_angle);
void	ft_calculate_hor_intercept(t_var_cast_ray *var, t_ray ray, t_player player);
void	ft_calculate_ver_intercept(t_var_cast_ray *var, t_ray ray, t_player player);
void	ft_find_hor_wall_hit_xy(t_data *data, t_var_cast_ray *var, t_ray *ray);
void	ft_find_ver_wall_hit_xy(t_data *data, t_var_cast_ray *var, t_ray *ray);
void	ft_fill_ray_data(t_ray *ray, t_var_cast_ray var, t_player player);
void		ft_generate_walls_projection(t_data *data);
void		ft_import_xpm_file(t_data *data, t_map *map);
void		ft_walls_projection(t_data *data, t_var_generate_walls_proj var, int i);
int		ft_get_pix_color(t_img *img, int x, int y);


//// display things
void	affiche_str(void *c);
void	affiche_list(t_list *l);
void	ft_display_tmap_map(t_map map);
void	ft_display_tmap(t_map map);
void	ft_display_chararray(char **map);
void	ft_render_rays(t_data *data);
#endif
