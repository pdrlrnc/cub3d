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
	int x_start_cont = x_mid_mid * 1 - SIZE_CONTAINER / 2;
	int x_end_cont = x_mid_mid * 1 + SIZE_CONTAINER / 2;

	int	y_mid = WIN_HEIGHT / 2;
	int y_start_cont = y_mid * 1 - SIZE_CONTAINER / 2;
	int y_end_cont = y_mid * 1 + SIZE_CONTAINER / 2;

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

void	init_2d_map(t_game *game)
{
	int nb_grids = max(game->scene->map_w, game->scene->map_h);
	while (SIZE_CONTAINER % nb_grids != 0)
		nb_grids++;
	game->nb_grids = nb_grids;
	int grid_size = SIZE_CONTAINER / nb_grids;
	game->grid_size = grid_size;

	// printf("SIZE_CONTAINER=%d\n", SIZE_CONTAINER);
	// printf("game->scene->map_w=%d\n", game->scene->map_w);
	// printf("game->scene->map_h=%d\n", game->scene->map_h);
	// printf("grid_size=%d\n", grid_size);
	// printf("nb_grids=%d\n", nb_grids);

	game->map2d = malloc(sizeof(t_grid *) * nb_grids);
	int	y = 0;
	while (y < game->scene->map_h)
	{
		game->map2d[y] = malloc(sizeof(t_grid) * nb_grids);
		int	x = 0;
		while (x < game->scene->map_w)
		{
			game->map2d[y][x].init = game->scene->map[y][x];
			game->map2d[y][x].x = x;
			game->map2d[y][x].y = y;
			game->map2d[y][x].pos_x = game->cont2d.x1 + x * grid_size;
			game->map2d[y][x].pos_y = game->cont2d.y1 + y * grid_size;
			if (game->scene->map[y][x] == '1')
				game->map2d[y][x].type = WALL;
			else if (game->scene->map[y][x] == '0')
				game->map2d[y][x].type = SPACE;
			else if (game->scene->map[y][x] == 'N')
				game->map2d[y][x].type = PERSO;
			else
				game->map2d[y][x].type = VOID;
			x++;
		}
		y++;
	}
}

void	draw_2d_grid(t_img *img, int color, t_game *game)
{
	int start_x = game->cont2d.x1;
	int start_y = game->cont2d.y1;
	int end_x = game->cont2d.x2;
	int end_y = game->cont2d.y2;
	int	i;

	i = 0;
	while (i <= SIZE_CONTAINER)
	{
		put_line(game, start_x + i, start_y, start_x + i, end_y, color);
		i += game->grid_size;
	}
	i = 0;
	while (i <= SIZE_CONTAINER)
	{
		put_line(game, start_x, start_y + i, end_x, start_y + i, color);
		i += game->grid_size;
	}
}

void	fill_square(t_img *img, int x, int y, int size, int color, t_game *game)
{
	int i = 0;
	while (i < size)
	{
		put_line(game, x + i, y, x + i, y + size, color);
		i++;
	}
}

void	draw_2d_map(t_img *img, int color, t_game *game)
{
	int x, y;

	y = 0;
	while (y < game->scene->map_h)
	{
		x = 0;
		while (x < game->scene->map_w)
		{
			if (game->map2d[y][x].type == WALL)
				fill_square(img, game->map2d[y][x].pos_x, game->map2d[y][x].pos_y, game->grid_size, color, game);
			x++;
		}
		y++;
	}
}

void print_map2d(t_game *game)
{
	int x, y;

	y = 0;
	while (y < game->scene->map_h)
	{
		x = 0;
		while (x < game->scene->map_w)
		{
			printf("game->map2d[%d][%d]=%c\n", y, x, game->map2d[y][x].init);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	hit(int pos_i_x, int pos_i_y, t_game *game)
{
	if (
		pos_i_y > game->cont2d.y1 + game->grid_size &&
		pos_i_x > game->cont2d.x1 + game->grid_size &&
		pos_i_y < game->cont2d.y2 - game->grid_size &&
		pos_i_x < game->cont2d.x2 - game->grid_size
	)
		return (0);
	return (1);
}

void	draw_2d_perso(t_img *img, int color, t_game *game)
{
	fill_square(img, game->perso.pos_x, game->perso.pos_y, game->perso.size, color, game);
	double perso_center_x = game->perso.pos_x + game->perso.size / 2;
	double perso_center_y = game->perso.pos_y + game->perso.size / 2;

	double rad = game->perso.angle * M_PI / 180;
	int i = 0;
	double pos_i_x = perso_center_x + cos(rad) * i;
	double pos_i_y = perso_center_y + sin(rad) * i;
	_put_pixel(img, pos_i_x, pos_i_y, color);
	while (!hit(pos_i_x, pos_i_y, game))
	{
		pos_i_x = perso_center_x + cos(rad) * i;
		pos_i_y = perso_center_y + sin(rad) * i;
		_put_pixel(img, pos_i_x, pos_i_y, color);
		i++;
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

	draw_containers(&game->img, 0x00FF0000, game);
	init_2d_map(game);
	draw_2d_map(&game->img, 0x00FFFFFF, game);
	draw_2d_grid(&game->img, 0x00FF0000, game);

	game->perso.size = 10;
	game->perso.pos_x = game->cont2d.x1 + game->scene->px * game->grid_size + game->grid_size / 2 - (game->perso.size / 2);
	game->perso.pos_y = game->cont2d.y1 + game->scene->py * game->grid_size + game->grid_size / 2 - (game->perso.size / 2);
	game->perso.angle = 270;
	draw_2d_perso(&game->img, 0x00FF0000 - 20000, game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	listen_events(game);
	mlx_loop(game->mlx);

	clean_scene(game->scene);
	return (0);
}
