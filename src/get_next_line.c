/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:51:22 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 14:51:26 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*gnl_realloc(char *result, int i, int *r)
{
	char	*new_result;

	*r = 0;
	if (result)
		while (*(result + *r))
			(*r)++;
	new_result = malloc(i + *r + 2);
	if (!new_result)
	{
		if (result)
			free(result);
		return (NULL);
	}
	if (!result)
		return (new_result);
	*r = 0;
	while (*(result + *r))
	{
		*(new_result + *r) = *(result + *r);
		(*r)++;
	}
	free(result);
	return (new_result);
}

static char	*ft_handle_new_line(char *buff, char *result, int i)
{
	int	buffer_index;
	int	result_index;

	result = gnl_realloc(result, i, &result_index);
	if (!result)
		return (NULL);
	buffer_index = 0;
	while (buffer_index <= i)
	{
		*(result + result_index) = *(buff + buffer_index);
		*(buff + buffer_index) = '\0';
		buffer_index++;
		result_index++;
	}
	*(result + result_index) = '\0';
	return (result);
}

static char	*ft_process_buffer(char *buff, int i)
{
	int	start;

	start = 0;
	while (*(buff + i) && i < 20)
	{
		*(buff + start) = *(buff + i);
		*(buff + i) = '\0';
		i++;
		start++;
	}
	return (buff);
}

static char	*get_next_line_cont(int fd, char *buffer, char *result, int bytes_read)
{
	int	i;

	result = NULL;
	while (bytes_read)
	{
		if (bytes_read != -2)
		{
			if (ft_strchr(buffer, '\n'))
				i = ft_strchr(buffer, '\n') - buffer;
			else
				i = ft_strlen(buffer) - 1;
			result = ft_handle_new_line(buffer, result, i);
			if (!result)
				return (NULL);
			buffer = ft_process_buffer(buffer, i + 1);
			if (ft_strchr(result, '\n'))
				return (result);
		}
		bytes_read = read(fd, buffer, 20);
		if (bytes_read == -1)
			return (free(result), NULL);
		buffer[bytes_read] = '\0';
	}
	if (!bytes_read && !result)
		return (NULL);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[20];
	char		*result;
	int			bytes_read;

	result = NULL;
	bytes_read = 1;
	if (!buffer[0])
		bytes_read = -2;
	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	return (get_next_line_cont(fd, buffer, result, bytes_read));
}
