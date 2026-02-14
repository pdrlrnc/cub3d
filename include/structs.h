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
	NO,
	SO,
	EA,
	WE,
	ERR
}	t_direction;

typedef struct s_wall_tex
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int	has_no;
	int	has_so;
	int	has_we;
	int	has_ea;
}		t_wall_tex;

typedef struct s_scene
{
	char		**map;
	t_list		*input_list;
	int			map_w;
	int			map_h;
	double		px;
	double		py;
	t_direction	spawn_direction;
	t_wall_tex	textures;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			sky_r;
	int			sky_g;
	int			sky_b;
	int			is_valid;
}		t_scene;

typedef struct s_point
{
	int	x;
	int	y;
	int	top;
}		t_point;

#endif
