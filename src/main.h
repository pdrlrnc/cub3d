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

#define WIN_WIDTH	1600
#define WIN_HEIGHT	800
#define SIZE_CONT 	WIN_WIDTH / 4
#define	SIZE_PERSO	10
#define SPEED		16000
#define RAD			20


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
	int	pos_x;
	int	pos_y;
	int	angle; // between 0 and 360
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

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	char	**map;
	t_img	img;
	t_perso	perso;
	t_keys	keys;
	t_scene	*scene;
	t_cont	cont2d;
	char	**map2d;
	t_cont	cont3d;
}	t_game;


// ##################################################
// # FUNCS
// ##################################################

void	put_line(t_game *game, int x1, int y1, int x2, int y2, int color);
void	draw_grid(t_img *img, t_game *game, int color);
void	_put_pixel(t_img *img, int x, int y, int color);
void	render_perso(t_game *game, int size);
void	listen_events(t_game *game);

// UTILS
int	max(int x1, int x2);

#endif // MAIN_H
