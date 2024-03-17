/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:53:35 by amakela           #+#    #+#             */
/*   Updated: 2024/03/12 20:53:38 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	component_check(t_map_data *data);

int	map_check(t_map_data *data)
{
	if (!component_check(data)
		|| !shape_check(data)
		|| !path_check(data->player, data))
	{
		free_arr(data->map, data->size.y);
		return (0);
	}
	return (1);
}

static int	component_check(t_map_data *data)
{
	int	y;
	int	x;

	y = -1;
	x = 0;
	while (data->map[++y])
	{
		while (data->map[y][x])
		{
			if (!ft_strchr("10PEC\n", data->map[y][x++]))
			{
				ft_printf("Error\nInvalid symbol found in the map\n");
				return (0);
			}
		}
		x = 0;
	}
	if (!symbol_check(data, 'P')
		|| !symbol_check(data, 'E')
		|| !symbol_check(data, 'C'))
		return (0);
	return (1);
}

int	symbol_check(t_map_data *data, char symbol)
{
	int	count;

	count = count_symbols(data->map, data, symbol);
	if (((symbol == 'P' || symbol == 'E') && (count != 1))
		|| (symbol == 'C' && count < 1))
	{
		ft_printf("Error\nInvalid amount of symbols found in the map\n");
		return (0);
	}
	if (symbol == 'C')
		data->collectibles = count;
	return (1);
}

int	count_symbols(char **map, t_map_data *data, char symbol)
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
				if (symbol == 'P')
				{
					data->player.y = y;
					data->player.x = x -1;
				}
				count++;
			}
		}
		y++;
		x = 0;
	}
	return (count);
}
