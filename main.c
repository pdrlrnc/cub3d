#include "main.h"

void	draw_map(t_img *img, int color)
{
	// t_img *img2 = img;
	int	map[5][7] = {
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '1'},
		{'1', '1', '0', '0', '0', 'N', '1'},
		{'1', '1', '1', '1', '1', '1', '1'},
	};
	int x = 0;
	while (x < 5)
	{
		int y = 0;
		while (y < 7)
		{
			// printf("Map[%d][%d] == %d\n", x, y, map[x][y]);
			if (map[x][y] == '1')
				draw_walls(img, ZOOM * x, ZOOM * y, ZOOM, color);
			if (map[x][y] == 'N')
				draw_walls(img, ZOOM * x, ZOOM * y, ZOOM / 10, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

int	main(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bitspp, &game->img.lsize, &game->img.endian);
	// draw_square(&game->img, 0, 0, 100, 0x00FFFFFF);
	draw_map(&game->img, 0x00FF0000);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, WIN_WIDTH / 2 - ZOOM * 3, WIN_HEIGHT / 2 - ZOOM * 3);
	mlx_loop(game->mlx);
	return (0);
}
