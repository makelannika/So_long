/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:22:06 by amakela           #+#    #+#             */
/*   Updated: 2024/02/22 18:22:34 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	t_map	*data;
	char	**map;

	int	i = 0;
	if (argc != 2)
		return (0);
	map = NULL;
	data = malloc(sizeof(t_map));
	if (!data)
		return (0);
	map = get_map(argv, map, data);
	if (!map)
	{
		free(data);
		return (0);
	}
	if (!map_check(map, data))
		return (0);
	ft_printf("map width: %d\n", data->size->x);
	ft_printf("map height: %d\n", data->size->y);
	ft_printf("collectibles: %d\n", data->collectibles);
	ft_printf("\n\n");
	while (map[i])
		ft_printf("%s", map[i++]);
	ft_printf("\n");
	ft_printf("player's coordinates y: %d x: %d\n", data->player->y, data->player->x);
	ft_printf("exit's coordinates y: %d x: %d\n\n", data->exit->y, data->exit->x);
	return (0);
}

char	**get_map(char **argv, char **map, t_map *data)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (get_map_height(fd, data) < 3)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	map = malloc(sizeof(char *) * (data->size->y + 1));
	if (!map)
		return (NULL);
	while (i < data->size->y)
	{
		map[i++] = get_next_line(fd);
		if (map[i - 1] == NULL)
			return (free_arr(map, i));
	}
	map[i] = NULL;
	return (map);
}

size_t	get_map_height(int fd, t_map *data)
{
	char	*line;
	t_point	*size;

	size = ft_calloc(1, sizeof(t_point));
	if (!size)
	{
		free(data);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		size->y++;
		free(line);
		line = get_next_line(fd);
	}
	data->size = size;
	return (size->y);
}

int	map_check(char **map, t_map *data)
{
	if (!component_check(map, data) || !shape_check(map, data) ||
		!path_check(map, data->player, data))
	{
		ft_printf("Invalid map\n");
		return (0);
	}
	ft_printf("Valid map\n\n");
	return (1);
}

int	component_check(char **map, t_map *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (!ft_strchr("10PEC\n", map[y][x++]))
				return (0);
		}
		y++;
		x = 0;
	}
	if (!symbol_check(map, data, 'P') || 
		!symbol_check(map, data, 'E') ||
		!symbol_check(map, data, 'C'))
		return (0);
	return (1);
}

int	symbol_check(char **map, t_map *data, char symbol)
{
	int	count;

	count = count_symbols(map, data, symbol);
	if (count == -1)
		return (0);
	if ((symbol == 'P' || symbol == 'E') && (count != 1))
	{
		ft_printf("player or exit != 1");
		return (0);
	}
	if (symbol == 'C' && count < 1)
	{
		ft_printf("no collectibles\n");
		return (0);
	}
	if (symbol == 'C')
		data->collectibles = count;
	return (1);
}

int	count_symbols(char **map, t_map *data, char symbol)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	x = 0;
	count = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x++] == symbol)
			{
				if (symbol == 'P' || symbol == 'E')
				{
					if (!set_coordinates(data, symbol, y, x -1))
						return (-1);
				}
				count++;
			}
		}
		y++;
		x = 0;
	}
	return (count);
}

int	shape_check(char **map, t_map *data)
{
	int	y;

	y = 1;
	data->size->x = ft_strlen(map[0]);
	while (map[y])
	{
		if ((int)ft_strlen(map[y]) != data->size->x)
			return (0);
		y++;
	}
	if (!wall_check(map, data))
		return (0);
	return (1);
}

int	wall_check(char **map, t_map *data)
{
	int	x;
	int	y;

	x = 0;
	y = data->size->y;
	while (map[y - 1][x])
	{
		if (!ft_strchr("1\n", map[y - 1][x++]))
			return (0);
	}
	while (y > 0)
	{
		y--;
		if (map[y][0] != '1' || map[y][data->size->x - 2] != '1')
			return (0);
	}
	x = 0;
	while (map[0][x])
	{
		if (!ft_strchr("1\n", map[0][x++]))
			return (0);
	}
	return (1);
}

int	path_check(char **map, t_point *player, t_map *data)
{
	int i;
	char **copy;

	i = 0;
	copy = malloc(sizeof(char *) * (data->size->y + 1));
	if (!copy)
	{
		free(map);
		free(data);
		return (-1);
	}
	while (i < data->size->y)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	fill_map(copy, *player);
	if (count_symbols(copy, data, 'C') || count_symbols(copy, data, 'E'))
	{
		free(copy);
		return (0);
	}
	free(copy);
	return (1);
}

void	fill_map(char **map, t_point curr)
{
	if (map[curr.y][curr.x] == '1')
		return ;
	map[curr.y][curr.x] = '1';
	fill_map(map, (t_point){curr.y - 1, curr.x});
	fill_map(map, (t_point){curr.y + 1, curr.x});
	fill_map(map, (t_point){curr.y, curr.x - 1});
	fill_map(map, (t_point){curr.y, curr.x + 1});
}

int	set_coordinates(t_map *data, char symbol, int y, int x)
{
	t_point *coordinates;

	coordinates = malloc(sizeof(t_point));
	if (!coordinates)
	{
		free(data);
		return (0);
	}
	coordinates->y = y;
	coordinates->x = x;
	if (symbol == 'P')
		data->player = coordinates;
	else if (symbol == 'E')
		data->exit = coordinates;
	return (1);
}
