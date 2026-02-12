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

/*
 * Need to refactor:
 *  - validate_input: should return the filled struct if the input is valid
 *  or NULL and in that case the program should exit cleanly
 *
 *  - get_input_values: should also get the values for the textures and the RGB
 *  for the ceiling and the sky
 *
 * - validate_map: implement floodfill to check if the map is okay. if not, clean
 *   and return NULL. 
 */

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
	get_input_values(scene, map_fd);
	print_scene(*scene);
	
	return (*scene);
}

void	get_input_values(t_scene **scene, int map_fd)
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
	read_config_lines(scene, list);
	read_map(scene, list);
	ft_lstclear(&list, free);
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
			(*scene)->map[i] = ft_strdup((char *) list->content);
			read_player_position(scene, (char *) list->content, i);
			i++;
		}
		list = list->next;
	}
	(*scene)->map[i] = NULL;
	return (1);
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
