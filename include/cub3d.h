/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:16:14 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 13:16:15 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 #define CUB3D_H

#include "structs.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "mapper.h"

void	check_malloc(void *ptr, void *to_free, int fd);
char	*get_next_line(int fd);

#endif
