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

int	get_textures(t_map_data *data)
{
	data->sand_t = mlx_load_png("./textures/sand.png");
	data->plant_t = mlx_load_png("./textures/plant.png");
	data->shell_t = mlx_load_png("./textures/shell.png");
	data->crab_t = mlx_load_png("./textures/crab.png");
	data->hole_t = mlx_load_png("./textures/exit.png");
	if (mlx_errno)
		return (0);
	data->sand = get_background(data, data->sand_t);
	data->plant = get_image(data, data->plant_t);
	data->shell = get_image(data, data->shell_t);
	data->crab = get_image(data, data->crab_t);
	data->hole = get_image(data, data->hole_t);
	if (mlx_errno)
		return (0);
	return (1);
}

mlx_image_t	*get_background(t_map_data *data, mlx_texture_t *texture)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(data->mlx, texture);
	if (!img || !mlx_resize_image(img, WIDTH * data->size.x,
			HEIGHT * data->size.y))
		return (NULL);
	return (img);
}

mlx_image_t	*get_image(t_map_data *data, mlx_texture_t *texture)
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

	y = -1;
	while (data->map[++y])
	{
		if (!draw_row(data, y))
			return (0);
	}
	data->hole->enabled = false;
	return (1);
}

int	draw_row(t_map_data *data, int y)
{
	int	x;
	int	idx;

	x = 0;
	idx = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == '1')
			idx = mlx_image_to_window(data->mlx, data->plant,
					x * WIDTH, y * HEIGHT);
		else if (data->map[y][x] == 'C')
			data->id_map[y][x] = mlx_image_to_window(data->mlx, data->shell,
					x * WIDTH, y * HEIGHT);
		else if (data->map[y][x] == 'P')
			idx = mlx_image_to_window(data->mlx, data->crab,
					x * WIDTH, y * HEIGHT);
		else if (data->map[y][x] == 'E')
			idx = mlx_image_to_window(data->mlx, data->hole,
					x * WIDTH, y * HEIGHT);
		if (idx < 0 || (data->map[y][x] == 'C' && data->id_map[y][x] < 0))
			return (0);
		x++;
	}
	return (1);
}
