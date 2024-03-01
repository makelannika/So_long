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
	t_map	*stats;
	char	**map;

	int	i = 0;
	if (argc != 2)
		return (0);
	map = NULL;
	stats = malloc(sizeof(t_map));
	if (!stats)
		return (0);
	map = get_map(argv, map, stats);
	if (!map)
	{
		free(stats);
		return (0);
	}
	map_check(map, stats);
	ft_printf("map width: %d\n", stats->width);
	ft_printf("map height: %d\n", stats->height);
	ft_printf("collectibles: %d\n", stats->collectibles);
	ft_printf("\n\n");
	while (map[i])
		ft_printf("%s", map[i++]);
	return (0);
}

char	**get_map(char **argv, char **map, t_map *stats)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (get_map_height(fd, stats) < 3)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	map = malloc(sizeof(char *) * (stats->height + 1));
	if (!map)
		return (NULL);
	while (i < stats->height)
	{
		map[i++] = get_next_line(fd);
		if (map[i - 1] == NULL)
			return (free_arr(map, i));
	}
	map[i] = NULL;
	return (map);
}

size_t	get_map_height(int fd, t_map *stats)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		stats->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (stats->height);
}

int	map_check(char **map, t_map *stats)
{
	if (!component_check(map, stats) || !shape_check(map, stats))
	{
		ft_printf("Invalid map\n");
		return (0);
	}
	ft_printf("Valid map\n");
	ft_printf("\n");
	return (1);
}

int	component_check(char **map, t_map *stats)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (!ft_strchr("10PEC\n", map[i][j++]))
				return (0);
		}
		i++;
		j = 0;
	}
	if (count_symbols(map, 'P') != 1 || count_symbols(map, 'E') != 1)
		return (0);
	stats->collectibles = count_symbols(map, 'C');
	if (stats->collectibles < 1)
		return (0);
	return (1);
}

int	count_symbols(char **map, char symbol)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j++] == symbol)
				count++;
		}
		i++;
		j = 0;
	}
	return (count);
}

int	shape_check(char **map, t_map *stats)
{
	int	y;

	y = 1;
	stats->width = ft_strlen(map[0]);
	while (map[y])
	{
		if (ft_strlen(map[y]) != stats->width)
			return (0);
		y++;
	}
	if (!wall_check(map, stats))
		return (0);
	return (1);
}

int	wall_check(char **map, t_map *stats)
{
	int	x;
	int	y;

	x = 0;
	y = stats->height;
	while (map[y - 1][x])
	{
		if (!ft_strchr("1\n", map[y - 1][x++]))
			return (0);
	}
	while (y > 0)
	{
		y--;
		if (map[y][0] != '1' || map[y][stats->width - 2] != '1')
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

// check valid path
