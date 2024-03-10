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

int	main(int argc, char **argv)
{
	t_map_data		*data;

	if (argc != 2)
		return (0);
	data = ft_calloc(1, sizeof(t_map_data));
	if (!data || !get_map(argv, data) || !map_check(data) || !get_id_map(data))
		return (0);
	so_long(data);
	free_id_map(data->id_map, data->size->y);
	free_data(data);
	return (0);
}

int	so_long(t_map_data *data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH * data->size->x,
			HEIGHT * data->size->y, "So_long", true);
	if (!data->mlx)
		return (0);
	if (!get_textures(data))
		return (0);
	if (mlx_image_to_window(data->mlx, data->sand, 0, 0 < 0))
		return (0);
	if (!draw_map(data))
		return (0);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	delete_textures(data);
	mlx_terminate(data->mlx);
	return (1);
}
