/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:48:47 by amakela           #+#    #+#             */
/*   Updated: 2024/03/17 19:48:50 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_extension(char *arg);
static int	game(t_map_data *data);

int	main(int argc, char **argv)
{
	t_map_data		data;

	if (argc != 2 || check_extension(argv[1]) != 0)
	{
		ft_printf("Error\nInvalid input\nEnter a .ber file\n");
		return (0);
	}
	if (!get_map(argv, &data) || !map_check(&data) || !get_id_map(&data))
		return (0);
	game(&data);
	free_id_map((&data)->id_map, (&data)->size.y);
	free_arr((&data)->map, (&data)->size.y);
	return (0);
}

static int	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	return (ft_strncmp(&arg[len - 4], ".ber", 4));
}

static int	game(t_map_data *data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH * data->size.x,
			HEIGHT * data->size.y, "So_long", true);
	if (!data->mlx)
		return (0);
	if (!get_textures(data)
		|| mlx_image_to_window(data->mlx, data->sand, 0, 0 < 0)
		|| !draw_map(data))
	{
		delete_textures(data);
		mlx_terminate(data->mlx);
		return (0);
	}
	mlx_key_hook(data->mlx, &movement, data);
	mlx_loop(data->mlx);
	if (data->crab->enabled == true)
		ft_printf("You exited the game\n");
	delete_textures(data);
	mlx_terminate(data->mlx);
	return (1);
}
