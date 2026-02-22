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
# include "../include/cub3d.h"


// ##################################################
// # VARS
// ##################################################

#define WIN_WIDTH		1600
#define WIN_HEIGHT		800
#define SIZE_CONTAINER	WIN_WIDTH / 4
#define	SIZE_PERSO		10
#define SPEED			12000
#define RAD				20
#define RAD_DIFF		25
#ifndef M_PI
# define M_PI			3.14159265358979323846
#endif


// ##################################################
// # ENUM
// ##################################################

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

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bitspp;
	int		lsize;
	int		endian;
}	t_img;

typedef struct s_perso {
	int		size;
	double	pos_x;
	double	pos_y;
	int		angle; // between 0 and 360
}	t_perso;

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
	void	*mlx;
	void	*mlx_win;
	char	**map;
	int		nb_grids;
	int		grid_size;
	t_img	img;
	t_perso	perso;
	t_keys	keys;
	t_scene	*scene;
	t_cont	cont2d;
	t_grid	**map2d;
	t_cont	cont3d;
}	t_game;


// ##################################################
// # FUNCS
// ##################################################

void	put_line(t_game *game, int x1, int y1, int x2, int y2, int color);
void	_put_pixel(t_img *img, int x, int y, int color);
void	listen_events(t_game *game);

// UTILS
int		max(int x1, int x2);

void	draw_containers(t_img *img, int color, t_game *game);
void	draw_2d_perso(t_img *img, int color, t_game *game);
void	init_2d_map(t_game *game);
void	draw_2d_map(t_img *img, int color, t_game *game);
void	draw_2d_grid(t_img *img, int color, t_game *game);
void	draw_2d_perso(t_img *img, int color, t_game *game);
void	draw_3d_view(t_game *game);

#endif // MAIN_H
