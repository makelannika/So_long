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
	if (data->background_txtr)
		mlx_delete_texture(data->background_txtr);
	if (data->wall_txtr)
		mlx_delete_texture(data->wall_txtr);
	if (data->player_txtr)
		mlx_delete_texture(data->player_txtr);
	if (data->collectible_txtr)
		mlx_delete_texture(data->collectible_txtr);
	if (data->exit_txtr)
		mlx_delete_texture(data->exit_txtr);
}

void	free_id_map(int	**id_map, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(id_map[i++]);
	free(id_map);
}
