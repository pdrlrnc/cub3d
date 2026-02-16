#include "main.h"

// void	draw_map(t_img *img, int color, t_game *game, int render_perso)
// {
// 	int x = 0;
// 	while (game->scene->map[x])
// 	{
// 		int y = 0;
// 		while (game->scene->map[x][y])
// 		{
// 			// printf("Map[%d][%d] == %d\n", x, y, game->scene->map[x][y]);
// 			if (game->scene->map[x][y] == '1')
// 				draw_wall(img, ZOOM * x, ZOOM * y, ZOOM, color);
// 			if (game->scene->map[x][y] == 'N' && render_perso)
// 			{
// 				game->perso.pos_x = x * ZOOM;
// 				game->perso.pos_y = y * ZOOM;
// 				game->perso.angle = 270;
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	draw_containers(t_img *img, int color, t_game *game)
{
	int	x_mid = WIN_WIDTH / 2;

	int	x_mid_mid = x_mid / 2;
	int x_start_cont = x_mid_mid * 1 - SIZE_CONT / 2;
	int x_end_cont = x_mid_mid * 1 + SIZE_CONT / 2;

	int	y_mid = WIN_HEIGHT / 2;
	int y_start_cont = y_mid * 1 - SIZE_CONT / 2;
	int y_end_cont = y_mid * 1 + SIZE_CONT / 2;

	game->cont2d.x1 = x_start_cont;
	game->cont2d.x2 = x_end_cont;
	game->cont2d.y1 = y_start_cont;
	game->cont2d.y2 = y_end_cont;

	put_line(game, x_mid, 0, x_mid, WIN_HEIGHT, color);
	put_line(game, x_start_cont, y_start_cont, x_end_cont, y_start_cont, color);
	put_line(game, x_start_cont, y_start_cont, x_start_cont, y_end_cont, color);
	put_line(game, x_end_cont, y_start_cont, x_end_cont, y_end_cont, color);
	put_line(game, x_start_cont, y_end_cont, x_end_cont, y_end_cont, color);

	x_start_cont = x_mid + x_start_cont;
	x_end_cont = x_mid + x_end_cont;

	game->cont3d.x1 = x_start_cont;
	game->cont3d.x2 = x_end_cont;
	game->cont3d.y1 = y_start_cont;
	game->cont3d.y2 = y_end_cont;

	put_line(game, x_start_cont, y_start_cont, x_end_cont, y_start_cont, color);
	put_line(game, x_start_cont, y_start_cont, x_start_cont, y_end_cont, color);
	put_line(game, x_end_cont, y_start_cont, x_end_cont, y_end_cont, color);
	put_line(game, x_start_cont, y_end_cont, x_end_cont, y_end_cont, color);
}

void	draw_2d_grid(t_img *img, int color, t_game *game)
{
	printf("game->scene->map_w=%d\n", game->scene->map_w);
	printf("game->scene->map_h=%d\n", game->scene->map_h);
	int test = max(game->scene->map_w, game->scene->map_h);
	while (SIZE_CONT % test != 0)
		test++;
	int GRID_SIZE = SIZE_CONT / test;

	int start_x = game->cont2d.x1;
	int start_y = game->cont2d.y1;
	int end_x = game->cont2d.x2;
	int end_y = game->cont2d.y2;
	int	i, i2;
	int x = 0;
	int y = 0;

	i = 0;
	while (i <= SIZE_CONT)
	{
		put_line(game, start_x + i, start_y, start_x + i, end_y, color);
		i2 = 0;
		while (i2 < GRID_SIZE && start_x + i + GRID_SIZE - 1 < end_x)
		{
			put_line(game, start_x + i + 1, start_y + i2, start_x + i + GRID_SIZE - 1, start_y + i2, color - 10000);
			i2++;
		}
		i += GRID_SIZE;
		x++;
	}
	i = 0;
	while (i <= SIZE_CONT)
	{
		put_line(game, start_x, start_y + i, end_x, start_y + i, color);
		i += GRID_SIZE;
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bitspp, &game->img.lsize, &game->img.endian);
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.up = 0;
	game->keys.down = 0;

	game->scene = validate_input(argc, argv);
	if (!game->scene)
		return (write(STDOUT_FILENO, "Error\n", 6), 1);

	game->perso.pos_x = game->cont2d.x1 + game->scene->px;
	game->perso.pos_y = game->cont2d.y1 + game->scene->py;
	game->perso.angle = 270;
	// draw_map(&game->img, 0x00FF0000, game, 1);
	draw_containers(&game->img, 0x00FF0000, game);
	draw_2d_grid(&game->img, 0x00FFFFFF, game);
	// draw_2d_map(&game->img, 0x00FFFFFF, game);
	// render_perso(game, SIZE_PERSO);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	listen_events(game);
	mlx_loop(game->mlx);

	clean_scene(game->scene);
	return (0);
}
