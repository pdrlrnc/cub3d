/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:47:53 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 11:47:56 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPER_H
#define MAPPER_H

int		validate_input(int argc, char**argv);
int		validate_map(int map_fd);
void	get_input_values(t_scene **scene, int map_fd);

#endif
