/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:40:32 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:40:35 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H


// ##################################################
// # LIBS
// ##################################################
# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>


// ##################################################
// # VARS
// ##################################################

#define WIDTH			1600
#define HEIGHT			800
#define SIZE_MAP		(WIDTH / 8)
#define PADDING_MAP		10
#define	SIZE_PLAYER		5
#define ANGLE_SPEED		0.5
#define RAD				20
#define RAD_DIFF		30
#define LINE(a, b, c, d, e) &(t_line){a, b, c, d, e}
#ifndef M_PI
# define M_PI			3.14159265358979323846
#endif


// ##################################################
// # ENUM
// ##################################################

typedef enum e_keys {
	ON_LEFT			= 65361,
	ON_UP			= 65362,
	ON_RIGHT		= 65363,
	ON_DOWN			= 65364,
	ON_ESC			= 65307,
	ON_DESTROY		= 17,
	ON_KEYPRESS		= 2,
	ON_KEYRELEASE	= 3,
	ON_M			= 109,
	ON_F			= 102,
}	e_keys;

typedef enum e_excode {
	SUCCESS		= 0,
	ALLOCATION	= 1,
	PARSING		= 2,
	INIT_GAME	= 3,
	INIT_MAP2D	= 4,
	INIT_PERSO	= 5,
	TEXTURES	= 6,
	COLORS		= 7,
	RENDERING	= 8,
}	e_excode;

typedef enum e_type {
	PERSO,
	VOID,
	SPACE,
	WALL,
	DOOR,
}	e_type;


// ##################################################
// # STRUCTS
// ##################################################

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		lsize;
	int		endian;
}	t_tex;

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	color;
}	t_line;

typedef struct s_ray
{
	double	px;
	double	py;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
}	t_ray;

typedef struct s_slice
{
	double	height;
	int		mid_y;
	int		start;
	int		end;
}	t_slice;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bitspp;
	int		lsize;
	int		endian;
}	t_img;

typedef struct s_player {
	int		size;
	double	pos_x;
	double	pos_y;
	double	angle; // between 0 and 360
}	t_player;

typedef struct s_keys {
	int	a;
	int	d;
	int	left;
	int	right;
	int	up;
	int	down;
}	t_keys;

typedef struct s_cont {
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	mid_y;
}	t_cont;

typedef struct s_grid {
	char			init;
	unsigned long	x;
	unsigned long	y;
	unsigned long	pos_x;
	unsigned long	pos_y;
	e_type			type;
}	t_grid;

typedef struct s_game {
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			nb_grids;
	int			grid_size;
	t_img		img;
	t_player	player;
	t_keys		keys;
	t_scene		*scene;
	t_cont		cont2d;
	t_grid		**map2d;
	t_cont		cont3d;
	int			nb_rays;
	int			minimap_active;
	int			fisheye;
	t_tex		tex_n;
	t_tex		tex_s;
	t_tex		tex_e;
	t_tex		tex_w;
	int			ceiling;
	int			floor;
	double		wall_x;
	t_ray		last_ray;
}	t_game;


// ##################################################
// # FUNCS
// ##################################################

void	put_line(t_game *game, t_line *l);
void	_put_pixel(t_img *img, int x, int y, int color);
void	listen_events(t_game *game);

void	fill_square(t_game *game, t_line *l, int size);

void	draw_3d_view(t_game *game, double init_angle);

void	draw_2d_grid(t_game *game, int color);
void	draw_2d_map(t_game *game, int color);
void	draw_2d_perso(t_game *game, int color);
void	draw_2d_perso_dir(t_game *game, int x, int y, int color);

int		hit(t_game *game, int pos_i_x, int pos_i_y);
int		cast_ray_dda(t_game *game, double angle, double *dist);

int		init_game(t_game *game);
void	set_2d_point(t_game *game, int x, int y);
int		init_2d_map(t_game *game);
int		init_player(t_game *game);

// UTILS
int		max(int x1, int x2);
int		in(char c, char *set);
double	normalize_angle(double angle);

int		render(t_game *game);

int		is_wall_at(t_game *game, double x, double y);
int		can_move(t_game *game, double new_x, double new_y);

int		_clean(t_game *game);
int		__exit(t_game *game, e_excode code);

t_tex	*get_wall_tex(t_game *game, t_ray *r);
int		load_texture(t_game *game, t_tex *tex, char *path);
int		load_all_textures(t_game *game);
void	draw_tex_col(t_game *game, int x, t_slice *s, t_tex *tex);

int		load_colors(t_game *game);

#endif // MAIN_H
