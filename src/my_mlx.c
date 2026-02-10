#include "../main.h"

void	_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bitspp / 8) + y * img->lsize);
	*(unsigned int*)dst = color;
}

void	draw_wall(t_img *img, int x, int y, int size, int color)
{
	int init_x = x;
	int init_y = y;

	while (x < init_x + size)
	{
		int y = init_y;
		while (y < init_y + size)
			_put_pixel(img, x, y++, color);
		x++;
	}
}

void	draw_perso(t_img *img, t_perso perso, int size, int color)
{
	int init_x = perso.pos_x;
	int init_y = perso.pos_y;

	double rad = perso.angle * 3.14 / 180;
	int i = -1;
	while (++i < 20)
		_put_pixel(img, perso.pos_x + cos(rad) * i, perso.pos_y + sin(rad) * i, color);
	while (perso.pos_x - size / 2 < init_x + size / 2)
	{
		perso.pos_y = init_y;
		while (perso.pos_y - size / 2 < init_y + size / 2)
			_put_pixel(img, perso.pos_x - size / 2, perso.pos_y++ - size / 2, color);
		perso.pos_x++;
	}
}

void	render_perso(t_game *game, int size)
{
	draw_perso(&game->img, game->perso, size, 0x00FFFFFF);
}
