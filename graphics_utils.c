/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:14:05 by amakela           #+#    #+#             */
/*   Updated: 2024/03/10 18:14:07 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*get_background(t_map_data *data, mlx_texture_t *texture);
static mlx_image_t	*get_image(t_map_data *data, mlx_texture_t *texture);

int	get_textures(t_map_data *data)
{
	data->background_txtr = mlx_load_png("./textures/sand.png");
	data->wall_txtr = mlx_load_png("./textures/plant.png");
	data->collectible_txtr = mlx_load_png("./textures/shell.png");
	data->player_txtr = mlx_load_png("./textures/crab.png");
	data->exit_txtr = mlx_load_png("./textures/exit.png");
	if (mlx_errno)
		return (0);
	data->b = get_background(data, data->background_txtr);
	data->w = get_image(data, data->wall_txtr);
	data->c = get_image(data, data->collectible_txtr);
	data->p = get_image(data, data->player_txtr);
	data->e = get_image(data, data->exit_txtr);
	if (mlx_errno)
		return (0);
	return (1);
}

static mlx_image_t	*get_background(t_map_data *data, mlx_texture_t *texture)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(data->mlx, texture);
	if (!img || !mlx_resize_image(img, WIDTH * data->size.x,
			HEIGHT * data->size.y))
		return (NULL);
	return (img);
}

static mlx_image_t	*get_image(t_map_data *data, mlx_texture_t *texture)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(data->mlx, texture);
	if (!img || !mlx_resize_image(img, WIDTH, HEIGHT))
		return (NULL);
	return (img);
}

int	draw_map(t_map_data *data)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	while (data->map[++y])
	{
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->w, x * WIDTH, y * HEIGHT);
			else if (data->map[y][x] == 'C')
				data->id_map[y][x] = mlx_image_to_window(data->mlx, data->c,
						x * WIDTH, y * HEIGHT);
			else if (data->map[y][x] == 'P')
				mlx_image_to_window(data->mlx, data->p, x * WIDTH, y * HEIGHT);
			else if (data->map[y][x] == 'E')
				mlx_image_to_window(data->mlx, data->e, x * WIDTH, y * HEIGHT);
			if (mlx_errno)
				return (0);
		}
		x = -1;
	}
	data->e->enabled = false;
	return (1);
}
