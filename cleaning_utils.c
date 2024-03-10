/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:18:40 by amakela           #+#    #+#             */
/*   Updated: 2024/03/10 18:18:42 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_textures(t_map_data *data)
{
	mlx_delete_texture(data->crab_t);
	mlx_delete_texture(data->hole_t);
	mlx_delete_texture(data->plant_t);
	mlx_delete_texture(data->sand_t);
	mlx_delete_texture(data->shell_t);
}

void	free_id_map(int	**id_map, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(id_map[i++]);
	free(id_map);
}

int	free_data(t_map_data *data)
{
	free_arr(data->map, data->size->y);
	free(data->size);
	free(data->player);
	free(data);
	return (0);
}
