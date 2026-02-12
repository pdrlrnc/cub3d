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
	t_list	*list;

	print_scene(*scene);
	list = get_input_values_to_list(map_fd);
	print_scene(*scene);
	read_config_lines(scene, list);
	read_map(scene, list);
	ft_lstclear(&list, free);

	
	return (*scene);
}

t_list	*get_input_values_to_list(int map_fd)
{
	char	*line;
	t_list	*list;

	line = get_next_line(map_fd);
	list = NULL;
	while (line)
	{
		if (ft_strchr(line, '\n') && ft_strlen(line) > 1)
			*(line + ft_strlen(line) - 1) = '\0';
		if (!list)
			list = ft_lstnew(ft_strdup(line));
		else if (ft_strlen(line) > 1)
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (list);

}

int	read_map(t_scene **scene, t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (!is_config_line((char *)list->content) && (*scene)->map_w == -1)
		{
			read_width_and_height(scene, list);
			(*scene)->map = malloc(sizeof(char *) * ((*scene)->map_h + 1));
		}
		if (!is_config_line((char *)list->content))
		{
			(*scene)->map[i] = normalize_line((char *) list->content, (*scene)->map_w);
			read_player_position(scene, (char *) list->content, i);
			i++;
		}
		list = list->next;
	}
	(*scene)->map[i] = NULL;
	ft_splitfree(normalize_map(scene));
	return (1);
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

void	read_player_position(t_scene **scene, char *line, int h)
{
	if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S')
		&& !ft_strchr(line, 'E') && !ft_strchr(line, 'W'))
		return ;
	if ((*scene)->spawn_direction != ERR)
	{
		(*scene)->is_valid = 0;
		return ;
	}
	(*scene)->py = h;
	if (ft_strchr(line, 'N'))
	{
		(*scene)->spawn_direction = NO;
		(*scene)->px = ft_strchr(line, 'N') - line;
	}
	if (ft_strchr(line, 'S'))
	{
		(*scene)->spawn_direction = SO;
		(*scene)->px = ft_strchr(line, 'S') - line;
	}
	if (ft_strchr(line, 'E'))
	{
		(*scene)->spawn_direction = EA;
		(*scene)->px = ft_strchr(line, 'E') - line;
	}
	if (ft_strchr(line, 'W'))
	{
		(*scene)->spawn_direction = WE;
		(*scene)->px = ft_strchr(line, 'W') - line;
	}
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

void	read_width_and_height(t_scene **scene, t_list *list)
{
	int	max_width;
	int	max_height;

	max_width = 0;
	max_height = 0;
	while (list)
	{
		if ((int)ft_strlen((char *)list->content) > max_width)
			max_width = ft_strlen((char *)list->content);
		max_height++;
		list = list->next;
	}
	(*scene)->map_w = max_width;
	(*scene)->map_h = max_height;
}

void	read_config_lines(t_scene **scene, t_list *list)
{
	char	**split;

	while (list && is_texture_line((char *)list->content))
	{
		split = ft_split((char *)list->content, ' ');
		read_texture(scene, split);
		ft_splitfree(split);
		list = list->next;
	}
	while (list && is_sky_or_floor((char *)list->content))
	{
		split = ft_split((char *)list->content, ' ');
		read_colours(scene, split);
		ft_splitfree(split);
		list = list->next;
	}
	check_validity(scene);
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

int	read_colours(t_scene **scene, char **split)
{
	char	**values;

	values = NULL;
	if (!ft_strcmp(split[0], "F"))
	{
		values = ft_split(split[1], ',');
		if (!ft_str_isdigit(values[0]) || !ft_str_isdigit(values[1])
				|| !ft_str_isdigit(values[2]))
			return (0);
		(*scene)->floor_r = ft_atoi(values[0]) % 255;
		(*scene)->floor_g = ft_atoi(values[1]) % 255;
		(*scene)->floor_b = ft_atoi(values[2]) % 255;
		ft_splitfree(values);
		return (1);
	}
	else if (!ft_strcmp(split[0], "C"))
	{
		values = ft_split(split[1], ',');
		if (!ft_str_isdigit(values[0]) || !ft_str_isdigit(values[1])
				|| !ft_str_isdigit(values[2]))
			return (0);
		(*scene)->sky_r = ft_atoi(values[0]) % 255;
		(*scene)->sky_g = ft_atoi(values[1]) % 255;
		(*scene)->sky_b = ft_atoi(values[2]) % 255;
		ft_splitfree(values);
		return (1);
	}
	return (0);
}

int	read_texture(t_scene **scene, char **split)
{
	if (!ft_strcmp(split[0], "NO"))
	{
		(*scene)->textures.tex_no = ft_strdup(split[1]);
		(*scene)->textures.has_no = 1;
		return (1);
	}
	else if (!ft_strcmp(split[0], "SO"))
	{
		(*scene)->textures.tex_so = ft_strdup(split[1]);
		(*scene)->textures.has_so = 1;
		return (1);
	}
	else if (!ft_strcmp(split[0], "EA"))
	{
		(*scene)->textures.tex_ea = ft_strdup(split[1]);
		(*scene)->textures.has_ea = 1;
		return (1);
	}
	else if (!ft_strcmp(split[0], "WE"))
	{
		(*scene)->textures.tex_we = ft_strdup(split[1]);
		(*scene)->textures.has_we = 1;
		return (1);
	}
	return (0);
}

t_scene	*get_bzeroed_scene(void)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	check_malloc(scene, NULL, -1);
	scene->map = NULL;
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
	ft_splitfree(scene->map);
	free(scene->textures.tex_no);
	free(scene->textures.tex_so);
	free(scene->textures.tex_we);
	free(scene->textures.tex_ea);
	free(scene);
}
