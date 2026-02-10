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
		if (!list)
			list = ft_lstnew(ft_strdup(line));
		else
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	read_config_lines(scene, list);
}

void	read_config_lines(t_scene **scene, t_list *list)
{
	char	**split;

	(void)scene;
	while (list)
	{
		split = ft_split((char *)list->content, ' ');
		read_texture(scene, split);
		list = list->next;
	}
}

void	read_texture(t_scene **scene, char **split)
{
	if (ft_strcmp(split[0], "NO"))
	{
		(*scene)->textures.tex_no = ft_strdup(split[1]);
		(*scene)->textures.has_no = 1;
	}
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
	scene->sky_rgb = -1;	
	scene->floor_rgb = -1;
	return (scene);
}
