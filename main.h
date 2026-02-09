#ifndef MAIN_H
#define MAIN_H


// ##################################################
// # LIBS
// ##################################################
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>


// ##################################################
// # VARS
// ##################################################
#define WIN_WIDTH	800
#define WIN_HEIGHT	800
#define ZOOM		50


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

typedef struct s_game {
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}	t_game;


// ##################################################
// # FUNCS
// ##################################################
void	_put_pixel(t_img *img, int x, int y, int color);
void	draw_walls(t_img *img, int x, int y, int size, int color);

#endif // MAIN_H
