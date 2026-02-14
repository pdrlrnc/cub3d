/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:21:53 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 13:22:04 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_scene	*validate_input(int argc, char**argv)
{
	int	fd;
	t_scene	*scene;

	if (argc != 2)
		return (write(STDERR_FILENO, "You need to give a .cub map as input\n", 37), NULL);
	if (ft_strlen(argv[1]) < 4 || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
		return (write(STDERR_FILENO, "Map must be *.cub\n", 18), NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write (STDERR_FILENO, "Unknown error opening map file\n", 31), NULL);
	scene = get_bzeroed_scene();
	return (validate_map(&(scene), fd));
}

t_scene	*validate_map(t_scene **scene, int map_fd)
{
	print_scene(*scene);
	get_input_values_to_list(scene, map_fd);
	print_scene(*scene);
	read_config_lines(scene, (*scene)->input_list);
	check_validity(scene);
	read_map(scene, (*scene)->input_list);

	return (*scene);
}

void	get_input_values_to_list(t_scene **scene, int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (ft_strchr(line, '\n') && ft_strlen(line) > 1)
			*(line + ft_strlen(line) - 1) = '\0';
		if (!(*scene)->input_list)
			(*scene)->input_list = ft_lstnew(ft_strdup(line));
		else if (ft_strlen(line) > 1)
			ft_lstadd_back(&(*scene)->input_list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
}

char	**normalize_map(t_scene **scene)
{
	char	**normalized_map;
	int	i;
	int	j;
	int	k;
	int	l;

	normalized_map = malloc(sizeof(char *) * ((*scene)->map_h + 3));
	i = 0;
	l = 0;
	while (i < ((*scene)->map_h + 2))
	{
		normalized_map[i] = malloc(sizeof(char) * ((*scene)->map_w + 3));
		j = 0;
		if (i == 0 || i == ((*scene)->map_h + 1))
		{
			while (j < ((*scene)->map_w + 2))
				normalized_map[i][j++] = 'V';
		}
		else
		{
			normalized_map[i][j++] = 'V';
			k = 0;
			while (k < (*scene)->map_w)
			{
				if ((*scene)->map[l][k] == ' ')
					normalized_map[i][j] = 'V';
				else
					normalized_map[i][j] = (*scene)->map[l][k];
				j++;
				k++;
			}
			l++;
			normalized_map[i][j++] = 'V';
		}
		normalized_map[i][j] = '\0';
		i++;
	}
	normalized_map[i] = NULL;
	printf("NORMALIZED MAP: \n");
	print_map(normalized_map);
	if (run_flood_fill(normalized_map, (*scene)->map_w + 2, (*scene)->map_h + 2))
		printf("\n\tMAP OK\n\n");
	else
		printf("\n\tMAP NOK\n\n");
	return (normalized_map);
}

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}


int	run_flood_fill(char **map, int width, int height)
{
	t_point	*stack;
	t_point	curr;
	int 	top;

	stack = create_stack(0,0, width, height);
	top = 0;
	while (top > -1)
	{
		curr = pop(stack, top);
		top--;
		if (is_walkable(map[curr.x][curr.y]))
		{
			free(stack);
			return (0);
		}
		if (map[curr.x][curr.y] == 'V')
		{
			map[curr.x][curr.y] = '*';
			if ((curr.x + 1) < height && map[curr.x + 1][curr.y] != '*')
				top = push(stack, top, curr.x + 1, curr.y);
			if ((curr.y + 1) < width && map[curr.x][curr.y + 1] != '*')
				top = push(stack, top, curr.x, curr.y + 1);
			if ((curr.x - 1) >= 0 && map[curr.x - 1][curr.y] != '*')
				top = push(stack, top, curr.x - 1, curr.y);
			if ((curr.y - 1) >= 0 && map[curr.x][curr.y - 1] != '*')
				top = push(stack, top, curr.x, curr.y - 1);
		}
	}
	free(stack);
	return (1);
}

char	*normalize_line(char *line, int map_w)
{
	char	*res;
	int	i;

	res = malloc(sizeof(char) * map_w + 1);
	i = 0;
	while (*(line + i))
	{
		*(res + i) = *(line + i);
		i++;
	}
	while (i < map_w)
	{
		*(res + i) = ' ';
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

int	is_config_line(char *line)
{
	if (is_sky_or_floor(line) || is_texture_line(line))
		return (1);
	return (0);
}

int	is_sky_or_floor(char *line)
{
	if (*line != 'F' && *line != 'C')
		return (0);
	return (1);
}

int	is_texture_line(char *line)
{
	if (*line != 'N' && *line != 'S' && *line != 'W' && *line != 'E')
		return (0);
	return (1);
}

void	check_validity(t_scene **scene)
{
	if (!(*scene)->textures.has_no || !(*scene)->textures.has_so
     		|| !(*scene)->textures.has_ea || !(*scene)->textures.has_we)
		(*scene)->is_valid = 0;
	if ((*scene)->floor_r == -1 || (*scene)->floor_g == -1 || (*scene)->floor_b == -1)
		(*scene)->is_valid = 0;
	if ((*scene)->sky_r == -1 || (*scene)->sky_g == -1 || (*scene)->sky_b == -1)
		(*scene)->is_valid = 0;

}

t_scene	*get_bzeroed_scene(void)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	check_malloc(scene, NULL, -1);
	scene->map = NULL;
	scene->input_list = NULL;
	scene->map_w = -1;
	scene->map_h = -1;
	scene->px = -1;
	scene->py = -1;
	scene->spawn_direction = ERR;
	scene->textures.tex_no = NULL;
	scene->textures.tex_so = NULL;
	scene->textures.tex_we = NULL;
	scene->textures.tex_ea = NULL;
	scene->textures.has_no = -1;
	scene->textures.has_so = -1;
	scene->textures.has_we = -1;
	scene->textures.has_ea = -1;
	scene->floor_r = -1;
	scene->floor_g = -1;
	scene->floor_b = -1;
	scene->sky_r = -1;
	scene->sky_g = -1;
	scene->sky_b = -1;
	scene->is_valid = 1;
	return (scene);
}

void	clean_scene(t_scene *scene)
{
	ft_lstclear(&(scene->input_list), free);
	ft_splitfree(scene->map);
	free(scene->textures.tex_no);
	free(scene->textures.tex_so);
	free(scene->textures.tex_we);
	free(scene->textures.tex_ea);
	free(scene);
}
