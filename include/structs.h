/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:48:30 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 11:48:46 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}		t_direction;

typedef struct s_text
{
	char	*type;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
}		t_text;

typedef struct s_scene
{
	char		**map;
	int			map_w;
	int			map_h;
	double		px;
	double		py;
	t_direction	spawn_direction;
	t_text		*textures;
	int			floor_rgb;
	int			sky_rgb;
}		t_scene;

#endif
