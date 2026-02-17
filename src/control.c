#include "main.h"

typedef enum e_cmds {
	ON_LEFT			= 65361,
	ON_UP			= 65362,
	ON_RIGHT		= 65363,
	ON_DOWN			= 65364,
	ON_ESC			= 65307,
	ON_DESTROY		= 17,
	ON_KEYPRESS		= 2,
	ON_KEYRELEASE	= 3,
} e_cmds;

static int	_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	printf("KEYCODE=%d\n", keycode);
	if (keycode == ON_LEFT)
		game->keys.left = 1;
	if (keycode == ON_UP)
		game->keys.up = 1;
	if (keycode == ON_RIGHT)
		game->keys.right = 1;
	if (keycode == ON_DOWN)
		game->keys.down = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == ON_ESC)
		_close(game);
	if (keycode == ON_LEFT)
		game->keys.left = 0;
	if (keycode == ON_UP)
		game->keys.up = 0;
	if (keycode == ON_RIGHT)
		game->keys.right = 0;
	if (keycode == ON_DOWN)
		game->keys.down = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	usleep(SPEED);

	if (game->keys.left)
		game->perso.angle -= 5;
	if (game->keys.right)
		game->perso.angle += 5;
	if (game->perso.angle >= 360)
		game->perso.angle -= 360;
	if (game->perso.angle < 0)
		game->perso.angle += 360;

	printf("ANGLE=%d\n", game->perso.angle);
	double rad = game->perso.angle * M_PI / 180;
	if (game->keys.up)
	{
		game->perso.pos_x += cos(rad);
		game->perso.pos_y += sin(rad);
	}
	if (game->keys.down)
	{
		game->perso.pos_x -= cos(rad);
		game->perso.pos_y -= sin(rad);
	}
	memset(game->img.addr, 0, game->img.lsize * WIN_HEIGHT);
	draw_containers(&game->img, 0x00FF0000, game);
	draw_2d_map(&game->img, 0x00FFFFFF, game);
	draw_2d_grid(&game->img, 0x00FF0000, game);
	draw_2d_perso(&game->img, 0x00FF0000 - 10000, game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (1);
}

void	listen_events(t_game *game)
{
	mlx_hook(game->mlx_win, ON_KEYPRESS, 1L << 0, key_press, game);
	mlx_hook(game->mlx_win, ON_KEYRELEASE, 1L << 1, key_release, game);

	mlx_hook(game->mlx_win, ON_DESTROY, 0, _close, game);

	mlx_loop_hook(game->mlx, game_loop, game);
}
