#include "main.h"

void	_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bitspp / 8) + y * img->lsize);
	*(unsigned int*)dst = color;
}



static void	drawh(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int		dx;
	int		dy;
	int		p;
	int		dir;

	dx = x2 - x1;
	dy = y2 - y1;
	dir = 1;
	if (dy < 0)
		dir = -dir;
	dy *= dir;
	p = 2 * dy - dx;
	while (x1 <= x2)
	{
		_put_pixel(&game->img, x1, y1, color);
		if (p >= 0)
		{
			y1 = y1 + dir;
			p = p - 2 * dx;
		}
		p = p + 2 * dy;
		x1 = x1 + 1;
	}
}

static void	drawv(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int		dx;
	int		dy;
	int		p;
	int		dir;

	dx = x2 - x1;
	dy = y2 - y1;
	dir = 1;
	if (dx < 0)
		dir = -dir;
	dx *= dir;
	p = 2 * dx - dy;
	while (y1 <= y2)
	{
		_put_pixel(&game->img, x1, y1, color);
		if (p >= 0)
		{
			x1 = x1 + dir;
			p = p - 2 * dy;
		}
		p = p + 2 * dx;
		y1 = y1 + 1;
	}
}

void	put_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	if (abs(x2 - x1) > abs(y2 - y1))
	{
		if (x1 > x2)
			drawh(game, x1, y1, x2, y2, color);
		else
			drawh(game, x1, y1, x2, y2, color);
	}
	else
	{
		if (y1 > y2)
			drawv(game, x1, y1, x2, y2, color);
		else
			drawv(game, x1, y1, x2, y2, color);
	}
}


void	draw_grid(t_img *img, t_game *game, int color)
{
	int	x = 0;
	int	y = 0;

	printf("HELLO\n");
	while (game->scene->map[x])
	{
		y = 0;
		while (y < game->scene->map[x][y])
		{
			printf("%c", game->scene->map[x][y]);
			_put_pixel(img, x, y++, color);
		}
		printf("\n");
		x++;
	}
}

// void	draw_wall(t_img *img, int x, int y, int size, int color)
// {
// 	int init_x = x;
// 	int init_y = y;

// 	while (x < init_x + size)
// 	{
// 		int y = init_y;
// 		while (y < init_y + size)
// 			_put_pixel(img, x, y++, color);
// 		x++;
// 	}
// }

static void	draw_perso(t_img *img, t_game *game, int size, int color)
{
	int init_x = game->perso.pos_x;
	int init_y = game->perso.pos_y;

	double rad = game->perso.angle * 3.14 / 180;
	int i = -1;
	// while (++i < 10)
	// 	_put_pixel(img, game->perso.pos_x + cos(rad) * i, game->perso.pos_y + sin(rad) * i, color);
	while (game->perso.pos_x - size / 2 < init_x + size / 2)
	{
		game->perso.pos_y = init_y;
		while (game->perso.pos_y - size / 2 < init_y + size / 2)
			_put_pixel(img, game->perso.pos_x - size / 2, game->perso.pos_y++ - size / 2, color);
			return;
		game->perso.pos_x++;
	}
}

void	render_perso(t_game *game, int size)
{
	draw_perso(&game->img, game, size, 0x00FFFFFF);
}
