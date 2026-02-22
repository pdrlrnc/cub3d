#include "main.h"

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
			{
				game->map2d[y][x].type = PERSO;
				game->perso.angle = 270;
			}
			else if (game->scene->map[y][x] == 'E')
			{
				game->map2d[y][x].type = PERSO;
				game->perso.angle = 0;
			}
			else if (game->scene->map[y][x] == 'S')
			{
				game->map2d[y][x].type = PERSO;
				game->perso.angle = 90;
			}
			else if (game->scene->map[y][x] == 'W')
			{
				game->map2d[y][x].type = PERSO;
				game->perso.angle = 180;
			}
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

int	hit(int pos_i_x, int pos_i_y, t_game *game)
{
	int rel_x = pos_i_x - game->cont2d.x1;
	int rel_y = pos_i_y - game->cont2d.y1;
	int grid_x = rel_x / game->grid_size;
	int grid_y = rel_y / game->grid_size;

	// Out of bounds
	if (grid_x < 0 || grid_x >= game->scene->map_w
		|| grid_y < 0 || grid_y >= game->scene->map_h)
		return (1);

	// Main wall check — this is essential!
	if (game->map2d[grid_y][grid_x].type == WALL)
		return (1);

	// Additional: grid boundary edge cases
	if (rel_x % game->grid_size == 0 && grid_x > 0
		&& game->map2d[grid_y][grid_x - 1].type == WALL)
		return (1);
	if (rel_y % game->grid_size == 0 && grid_y > 0
		&& game->map2d[grid_y - 1][grid_x].type == WALL)
		return (1);

	return (0);
}

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

void	draw_2d_perso_dir(t_img *img, int x, int y, int color, t_game *game, int nb_lines)
{
	double init_angle;
	if (nb_lines == 1)
		init_angle = game->perso.angle;
	else
		init_angle = game->perso.angle - RAD_DIFF;
	double step = (RAD_DIFF * 2) / nb_lines;

	int j = 0;
	while (j < nb_lines)
	{
		double rad = normalize_angle(init_angle + step * j) * M_PI / 180;
		int i = 0;
		double pos_i_x = x + cos(rad) * i;
		double pos_i_y = y + sin(rad) * i;
		_put_pixel(img, pos_i_x, pos_i_y, color);
		while (!hit(pos_i_x, pos_i_y, game))
		{
			pos_i_x = x + cos(rad) * i;
			pos_i_y = y + sin(rad) * i;
			_put_pixel(img, pos_i_x, pos_i_y, color);
			i++;
		}
		j++;
	}
	double rad = game->perso.angle * M_PI / 180;
}


void	draw_2d_perso(t_img *img, int color, t_game *game)
{
	fill_square(img, game->perso.pos_x, game->perso.pos_y, game->perso.size, color, game);
	double perso_center_x = game->perso.pos_x + game->perso.size / 2;
	double perso_center_y = game->perso.pos_y + game->perso.size / 2;

	draw_2d_perso_dir(img, perso_center_x, perso_center_y, color, game, 50);
	draw_2d_perso_dir(img, perso_center_x, perso_center_y, color - 1000, game, 1);
}

double	cast_ray(t_game *game, double angle, int draw_2d)
{
	double rad = normalize_angle(angle) * M_PI / 180;
	double px = game->perso.pos_x + game->perso.size / 2;
	double py = game->perso.pos_y + game->perso.size / 2;
	double cos_a = cos(rad);
	double sin_a = sin(rad);
	int i = 0;
	double pos_x, pos_y;

	while (1)
	{
		pos_x = px + cos_a * i;
		pos_y = py + sin_a * i;
		if (draw_2d)
			_put_pixel(&game->img, pos_x, pos_y, 0x00FFFF00);
		if (hit(pos_x, pos_y, game))
			break ;
		i++;
	}
	// Return euclidean distance
	return (sqrt((pos_x - px) * (pos_x - px) + (pos_y - py) * (pos_y - py)));
}

void	draw_3d_view(t_game *game)
{
	int		nb_rays = game->cont3d.x2 - game->cont3d.x1; // one ray per pixel column
	double	init_angle = normalize_angle(game->perso.angle - RAD_DIFF);
	double	angle_step = (RAD_DIFF * 2.0) / nb_rays;
	int		col;

	col = 1;
	while (col < nb_rays - 1)
	{
		double ray_angle = normalize_angle(init_angle + angle_step * col);

		// 1. Cast ray, get raw distance
		double raw_dist = cast_ray(game, ray_angle, 1);

		// 2. Fix fisheye
		double angle_diff = ray_angle - game->perso.angle;
		double perp_dist = raw_dist * cos(angle_diff * M_PI / 180);

		// 3. Calculate wall height (tweak the constant to taste)
		double wall_height = (game->grid_size * SIZE_CONTAINER) / perp_dist;
		if (wall_height > SIZE_CONTAINER)
			wall_height = SIZE_CONTAINER;

		// 4. Calculate where to draw the wall slice
		int cont3d_mid_y = (game->cont3d.y1 + game->cont3d.y2) / 2;
		int draw_start = cont3d_mid_y - (int)(wall_height / 2);
		if (draw_start < game->cont3d.y1 + 1)
			draw_start = game->cont3d.y1 + 1;
		int draw_end = cont3d_mid_y + (int)(wall_height / 2);
		if (draw_end > game->cont3d.y2 - 1)
			draw_end = game->cont3d.y2 - 1;
		int draw_x = game->cont3d.x1 + col;

		// 5. Draw ceiling, wall, floor
		put_line(game, draw_x, game->cont3d.y1 + 1, draw_x, draw_start, 0x00333333);  // ceiling
		put_line(game, draw_x, draw_start, draw_x, draw_end, 0x00AAAAAA);          // wall
		put_line(game, draw_x, draw_end, draw_x, game->cont3d.y2 - 1, 0x00666666);     // floor

		col++;
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
	draw_2d_perso(&game->img, 0x00FF0000 - 20000, game);
	draw_3d_view(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	listen_events(game);
	mlx_loop(game->mlx);

	clean_scene(game->scene);
	return (0);
}
