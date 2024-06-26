/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:07:10 by amakela           #+#    #+#             */
/*   Updated: 2024/03/10 18:08:51 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_left(t_map_data *data, int y, int x);
static void	move_up(t_map_data *data, int y, int x);
static void	move_right(t_map_data *data, int y, int x);
static void	move_down(t_map_data *data, int y, int x);

void	movement(mlx_key_data_t keydata, void *mapdata)
{
	t_map_data	*data;

	data = mapdata;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(data, data->player.y, data->player.x);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(data, data->player.y, data->player.x);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(data, data->player.y, data->player.x);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(data, data->player.y, data->player.x);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

static void	move_left(t_map_data *data, int y, int x)
{
	if (data->map[y][x - 1] != '1')
	{
		{
			data->player.x -= 1;
			data->p->instances->x = (data->player.x * WIDTH);
			data->moves += 1;
			ft_printf("Moves: %d\n", data->moves);
			if (data->id_map[y][x - 1] > -1)
			{
				data->c->instances[data->id_map[y][x - 1]].enabled = false;
				data->id_map[y][x - 1] = -1;
				data->collectibles--;
				if (data->collectibles == 0)
					data->e->enabled = true;
			}
			else if (data->map[y][x - 1] == 'E' && data->e->enabled == true)
			{
				data->p->enabled = false;
				ft_printf("You won!\n");
				mlx_close_window(data->mlx);
			}
		}
	}
}

static void	move_up(t_map_data *data, int y, int x)
{
	if (data->map[y - 1][x] != '1')
	{
		{
			data->player.y -= 1;
			data->p->instances->y = (data->player.y * WIDTH);
			data->moves += 1;
			ft_printf("Moves: %d\n", data->moves);
			if (data->id_map[y - 1][x] > -1)
			{
				data->c->instances[data->id_map[y - 1][x]].enabled = false;
				data->id_map[y - 1][x] = -1;
				data->collectibles--;
				if (data->collectibles == 0)
					data->e->enabled = true;
			}
			else if (data->map[y - 1][x] == 'E' && data->e->enabled == true)
			{
				data->p->enabled = false;
				ft_printf("You won!\n");
				mlx_close_window(data->mlx);
			}
		}
	}
}

static void	move_right(t_map_data *data, int y, int x)
{
	if (data->map[y][x + 1] != '1')
	{
		{
			data->player.x += 1;
			data->p->instances->x = (data->player.x * HEIGHT);
			data->moves += 1;
			ft_printf("Moves: %d\n", data->moves);
			if (data->id_map[y][x + 1] > -1)
			{
				data->c->instances[data->id_map[y][x + 1]].enabled = false;
				data->id_map[y][x + 1] = -1;
				data->collectibles--;
				if (data->collectibles == 0)
					data->e->enabled = true;
			}
			else if (data->map[y][x + 1] == 'E' && data->e->enabled == true)
			{
				data->p->enabled = false;
				ft_printf("You won!\n");
				mlx_close_window(data->mlx);
			}
		}
	}
}

static void	move_down(t_map_data *data, int y, int x)
{
	if (data->map[y + 1][x] != '1')
	{
		{
			data->player.y += 1;
			data->p->instances->y = (data->player.y * HEIGHT);
			data->moves += 1;
			ft_printf("Moves: %d\n", data->moves);
			if (data->id_map[y + 1][x] > -1)
			{
				data->c->instances[data->id_map[y + 1][x]].enabled = false;
				data->id_map[y + 1][x] = -1;
				data->collectibles--;
				if (data->collectibles == 0)
					data->e->enabled = true;
			}
			else if (data->map[y + 1][x] == 'E' && data->e->enabled == true)
			{
				data->p->enabled = false;
				ft_printf("You won!\n");
				mlx_close_window(data->mlx);
			}
		}
	}
}
