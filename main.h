#ifndef MAIN_H
#define MAIN_H


// ##################################################
// # LIBS
// ##################################################
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>



// ##################################################
// # VARS
// ##################################################
#define WIN_WIDTH	800
#define WIN_HEIGHT	800
#define ZOOM		50
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

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	t_perso	perso;
	t_keys	keys;
}	t_game;


// ##################################################
// # FUNCS
// ##################################################
void	draw_map(t_img *img, int color, t_game *game, int render_perso);
void	_put_pixel(t_img *img, int x, int y, int color);
void	draw_wall(t_img *img, int x, int y, int size, int color);
void	render_perso(t_game *game, int size);
void	listen_events(t_game *game);

#endif // MAIN_H
