/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:52:48 by amakela           #+#    #+#             */
/*   Updated: 2024/03/12 20:52:53 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	wall_check(t_map_data *data);
static char	**get_copy(char **copy, t_map_data *data);
static void	fill_map(char **map, t_point curr);

int	shape_check(t_map_data *data)
{
	int	y;

	y = 1;
	data->size.x = ft_strlen(data->map[0]);
	while (data->map[y])
	{
		if ((int)ft_strlen(data->map[y]) != data->size.x)
		{
			ft_printf("Error\nMap has an invalid shape\n");
			return (0);
		}
		y++;
	}
	if (data->size.x > 150 || data->size.y > 150)
	{
		ft_printf("Error\nMap too big\n");
		return (0);
	}
	if (!wall_check(data))
	{
		ft_printf("Error\nMap is not surrounded by walls\n");
		return (0);
	}
	data->size.x -= 1;
	return (1);
}

static int	wall_check(t_map_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = data->size.y;
	while (data->map[y - 1][x])
	{
		if (!ft_strchr("1\n", data->map[y - 1][x++]))
			return (0);
	}
	while (y > 0)
	{
		y--;
		if (data->map[y][0] != '1' || data->map[y][data->size.x - 2] != '1')
			return (0);
	}
	x = 0;
	while (data->map[0][x])
	{
		if (!ft_strchr("1\n", data->map[0][x++]))
			return (0);
	}
	return (1);
}

int	path_check(t_point player, t_map_data *data)
{
	char	**copy;

	copy = malloc(sizeof(char *) * (data->size.y + 1));
	if (!copy)
		return (0);
	if (!get_copy(copy, data))
		return (0);
	fill_map(copy, player);
	if (count_symbols(copy, data, 'C') || count_symbols(copy, data, 'E'))
	{
		free_arr(copy, data->size.y);
		ft_printf("Error\nNo valid path found in the map\n");
		return (0);
	}
	free_arr(copy, data->size.y);
	return (1);
}

static char	**get_copy(char **copy, t_map_data *data)
{
	int	i;

	i = -1;
	while (++i < data->size.y)
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			free_arr(copy, i);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

static void	fill_map(char **map, t_point curr)
{
	if (map[curr.y][curr.x] == '1')
		return ;
	map[curr.y][curr.x] = '1';
	fill_map(map, (t_point){curr.y - 1, curr.x});
	fill_map(map, (t_point){curr.y + 1, curr.x});
	fill_map(map, (t_point){curr.y, curr.x - 1});
	fill_map(map, (t_point){curr.y, curr.x + 1});
}
