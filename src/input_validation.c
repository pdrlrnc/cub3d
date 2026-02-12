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
			(*scene)->map = malloc(sizeof(char *) * (*scene)->map_h);
		}
		if (!is_config_line((char *)list->content))
			(*scene)->map[i] = ft_strdup((char *) list->content);
		list = list->next;
	}
	return (1);
}

int	is_config_line(char *line)
{
	if (*line != 'N' && *line != 'S' && *line != 'W'
     			&& *line != 'E' && *line != 'F' && *line != 'C')
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

	while (list)
	{
		split = ft_split((char *)list->content, ' ');
		read_texture(scene, split);
		read_colours(scene, split);
		ft_splitfree(split);
		list = list->next;
	}
}

int	read_colours(t_scene **scene, char **split)
{
	char	**values;

	values = NULL;
	if (!ft_strcmp(split[0], "F"))
	{
		values = ft_split(split[1], ',');
		(*scene)->floor_r = ft_atoi(values[0]) % 255;
		(*scene)->floor_g = ft_atoi(values[1]) % 255;
		(*scene)->floor_b = ft_atoi(values[2]) % 255;
		ft_splitfree(values);
		return (1);
	}
	else if (!ft_strcmp(split[0], "C"))
	{
		values = ft_split(split[1], ',');
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
	scene->textures.tex_no = NULL;
	scene->textures.tex_so = NULL;
	scene->textures.tex_we = NULL;
	scene->textures.tex_ea = NULL;
	scene->textures.has_no = -1;
	scene->textures.has_so = -1;
	scene->textures.has_we = -1;
	scene->textures.has_ea = -1;
	scene->floor_r = 0;
	scene->floor_g = 0;
	scene->floor_b = 0;
	scene->sky_r = 0;
	scene->sky_g = 0;
	scene->sky_b = 0;
	return (scene);
}
