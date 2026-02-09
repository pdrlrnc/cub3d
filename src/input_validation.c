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

int	validate_input(int argc, char**argv)
{
	int	fd;

	if (argc != 2)
	{
		write(STDERR_FILENO, "You need to give a .cub map as input\n", 37);
		return (0);
	}
	if (ft_strlen(argv[1]) < 4 || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
	{
		write(STDERR_FILENO, "Map must be *.cub\n", 18);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write (STDERR_FILENO, "Unknown error opening map file\n", 31);
		return (0);
	}
	return (validate_map(fd));
}

int	validate_map(int map_fd)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	check_malloc(scene, NULL, map_fd);
	get_map(&scene, map_fd);
	
	return (map_fd);
}

void	get_map(t_scene **scene, int map_fd)
{
	char	*line;
	t_list	*list;
	t_list	*aux;
	int	i;

	line = get_next_line(map_fd);
	while (line)
	{
		if (!list)
			list = ft_lstnew(ft_strdup(line));
		else
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(map_fd);
	}
	(*scene)->map = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	check_malloc((*scene)->map, *scene, map_fd);
	i = 0;
	aux = list;
	while (aux)
	{
		((*scene)->map)[i] = malloc(sizeof(char) * ft_strlen((char *)aux->content));
		if (!((*scene)->map)[i])
		{
			ft_splitfree_error((*scene)->map, i);
			check_malloc(NULL, *scene, map_fd);
		}
		((*scene)->map)[i] = ft_strdup(aux->content);
		aux = aux->next;
	}
}
