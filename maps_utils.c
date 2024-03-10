/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:26:12 by amakela           #+#    #+#             */
/*   Updated: 2024/03/10 18:26:14 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

char	**get_map(char **argv, t_map_data *data)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	get_map_height(fd, data);
	close(fd);
	if (data->size->y == 0)
		return (NULL);
	data->map = malloc(sizeof(char *) * (data->size->y + 1));
	if (!data->map)
	{
		free(data->size);
		free(data);
		return (NULL);
	}
	fd = open(argv[1], O_RDONLY);
	copy_map(data, fd);
	return (data->map);
}

void	get_map_height(int fd, t_map_data *data)
{
	char	*line;

	data->size = ft_calloc(1, sizeof(t_point));
	if (!data->size)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		data->size->y++;
		free(line);
		line = get_next_line(fd);
	}
	if (data->size->y == 0)
	{
		ft_printf("Error\nInvalid map\n");
		free(data->size);
		free(data);
	}
}

void	copy_map(t_map_data *data, int fd)
{
	int	i;

	i = 0;
	while (i < data->size->y)
	{
		data->map[i++] = get_next_line(fd);
		if (data->map[i - 1] == NULL)
		{
			free(data->size);
			free(data);
			free_arr(data->map, i);
			return ;
		}
	}
	data->map[i] = NULL;
}

int	**get_id_map(t_map_data *data)
{
	int	i;

	i = 0;
	data->id_map = malloc(data->size->y * sizeof(int *));
	if (!data->id_map)
	{
		free_data(data);
		return (NULL);
	}
	while (i < data->size->y)
	{
		data->id_map[i] = malloc(data->size->x * sizeof(int));
		if (!data->id_map[i])
		{
			free_id_map(data->id_map, i);
			free_data(data);
			return (NULL);
		}
		i++;
	}
	fill_id_map(data);
	return (data->id_map);
}

void	fill_id_map(t_map_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->size->y)
	{
		while (x < data->size->x)
		{
			data->id_map[y][x] = -1;
			x++;
		}
		y++;
		x = 0;
	}
}
