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
	{
		write(STDERR_FILENO, "You need to give a .cub map as input\n", 37);
		exit(2);
	}
	if (ft_strlen(argv[1]) < 4 || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
	{
		write(STDERR_FILENO, "Map must be *.cub\n", 18);
		exit(3);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write (STDERR_FILENO, "Unknown error opening map file\n", 31);
		exit(4);
	}
	scene = get_bzeroed_scene();
	return (validate_map(&(scene), fd));
}

t_scene	*validate_map(t_scene **scene, int map_fd)
{
	char	**normalized_map;

	read_input_values_to_list(scene, map_fd);
	read_config_lines(scene, (*scene)->input_list);
	read_map(scene, (*scene)->input_list);
	check_validity(scene);
	if (!(*scene)->is_valid)
		return (clean_scene(*scene), NULL);
	normalized_map = normalize_map(scene);
	if (!run_flood_fill(scene, normalized_map))
	{
		ft_splitfree(normalized_map);
		return (clean_scene(*scene), NULL);
	}
	ft_splitfree(normalized_map);
	return (*scene);
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

t_scene	*get_bzeroed_scene(void)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
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
