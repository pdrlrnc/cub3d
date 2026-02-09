#include "../main.h"

void	_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bitspp / 8) + y * img->lsize);
	*(unsigned int*)dst = color;
}

void	draw_walls(t_img *img, int x, int y, int size, int color)
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
