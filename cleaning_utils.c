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
	if (data->sand_t)
		mlx_delete_texture(data->sand_t);
	if (data->plant_t)
		mlx_delete_texture(data->plant_t);
	if (data->crab_t)
		mlx_delete_texture(data->crab_t);
	if (data->shell_t)
		mlx_delete_texture(data->shell_t);
	if (data->hole_t)
		mlx_delete_texture(data->hole_t);
}

void	free_id_map(int	**id_map, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(id_map[i++]);
	free(id_map);
}
