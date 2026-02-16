#include "main.h"

void	draw_map(t_img *img, int color, t_game *game, int render_perso)
{
	// t_img *img2 = img;
	int	map[5][7] = {
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', 'N', '1'},
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
				draw_wall(img, ZOOM * x, ZOOM * y, ZOOM, color);
			if (map[x][y] == 'N' && render_perso)
			{
				game->perso.pos_x = x * ZOOM;
				game->perso.pos_y = y * ZOOM;
				game->perso.angle = 270;
			}
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
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.up = 0;
	game->keys.down = 0;
	draw_map(&game->img, 0x00FF0000, game, 1);
	render_perso(game, SIZE_PERSO);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, WIN_WIDTH / 2 - ZOOM * 3, WIN_HEIGHT / 2 - ZOOM * 3);
	listen_events(game);
	mlx_loop(game->mlx);
	return (0);
}
