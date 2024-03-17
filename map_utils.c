/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:53:13 by amakela           #+#    #+#             */
/*   Updated: 2024/03/12 20:53:17 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

char	**get_map(char **argv, t_map_data *data)
{
	int		i;
	int		fd;
	int		flag;

	i = 0;
	flag = 0;
	fd = open(argv[1], O_RDONLY);
	get_map_height(fd, data, &flag);
	if (data->size.y == 0 || flag)
		return (NULL);
	data->map = malloc(sizeof(char *) * (data->size.y + 1));
	if (!data->map)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	copy_map(data, fd, &flag);
	return (data->map);
}

void	get_map_height(int fd, t_map_data *data, int *flag)
{
	char	*line;

	if (read(fd, 0, 0) < 0)
	{
		ft_printf("Error\nUnable to read the file\n");
		return ;
	}
	data->size.y = 0;
	line = get_next_line(fd, flag);
	while (line && !*flag)
	{
		data->size.y++;
		free(line);
		line = get_next_line(fd, flag);
	}
	if (flag)
		free(line);
	close(fd);
	if (data->size.y == 0 && !*flag)
		ft_printf("Error\nEmpty map\n");
}

void	copy_map(t_map_data *data, int fd, int *flag)
{
	int	i;

	i = 0;
	while (i < data->size.y)
	{
		data->map[i++] = get_next_line(fd, flag);
		if (data->map[i - 1] == NULL)
		{
			free_arr(data->map, i);
			close(fd);
			return ;
		}
	}
	data->map[i] = NULL;
	close(fd);
}

int	**get_id_map(t_map_data *data)
{
	int	i;

	i = 0;
	data->id_map = malloc(data->size.y * sizeof(int *));
	if (!data->id_map)
	{
		free_arr(data->map, data->size.y);
		return (NULL);
	}
	while (i < data->size.y)
	{
		data->id_map[i] = malloc(data->size.x * sizeof(int));
		if (!data->id_map[i])
		{
			free_id_map(data->id_map, i);
			free_arr(data->map, data->size.y);
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
	while (y < data->size.y)
	{
		while (x < data->size.x)
		{
			data->id_map[y][x] = -1;
			x++;
		}
		y++;
		x = 0;
	}
}
