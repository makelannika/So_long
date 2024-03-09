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
#include <fcntl.h>

#define HEIGHT 100
#define WIDTH 100

int	main(int argc, char **argv)
{
	t_map_data		*data;
	char			**map;

	int	i = 0;
	if (argc != 2)
		return (0);
	map = NULL;
	data = ft_calloc(1, sizeof(t_map_data));
	if (!data)
		return (0);
	map = get_map(argv, map, data);
	if (!map)
	{
		free(data);
		return (0);
	}
	if (!map_check(map, data))
		return (0);
	ft_printf("map width: %d\n", data->size->x);
	ft_printf("map height: %d\n", data->size->y);
	ft_printf("collectibles: %d\n", data->collectibles);
	ft_printf("\n");
	while (map[i])
		ft_printf("%s", map[i++]);
	ft_printf("\n");
	get_id_map(data);
	ft_printf("player's coordinates y: %d x: %d\n", data->player->y, data->player->x);
	so_long(data);
	free_data(data);
	return (0);
}

int	so_long(t_map_data *data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH * data->size->x, HEIGHT * data->size->y, "So_long", true);
	if (!data->mlx)
		return(0);
	if (!get_textures(data))
		return (0);
	if (mlx_image_to_window(data->mlx, data->sand, 0, 0 < 0))
		return(0);
	if (!draw_map(data))
		return (0);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (1);
}

int	draw_map(t_map_data *data)
{
	int	y = 0;
	int	x = 0;
	int id = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
			{
				if (mlx_image_to_window(data->mlx, data->plant, x * WIDTH, y * HEIGHT) < 0)
					return(0);
			}
			else if (data->map[y][x] == 'C')
			{
				id = mlx_image_to_window(data->mlx, data->shell, x * WIDTH, y * HEIGHT);
				if (id < 0)
					return(0);
				data->id_map[y][x] = id;
			}
			else if (data->map[y][x] == 'P')
			{
				if (mlx_image_to_window(data->mlx, data->crab, x * WIDTH, y * HEIGHT) < 0)
					return(0);
			}
			else if (data->map[y][x] == 'E')
			{
				if (mlx_image_to_window(data->mlx, data->hole, x * WIDTH , y * HEIGHT) < 0)
					return(0);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (1);
}

int	get_textures(t_map_data *data)
{
	mlx_texture_t	*sand;
	mlx_texture_t	*plant;
	mlx_texture_t	*shell;
	mlx_texture_t	*crab;
	mlx_texture_t	*hole;

	sand = mlx_load_png("./sand.png");
	plant = mlx_load_png("./plant.png");
	shell = mlx_load_png("./shell5.png");
	crab = mlx_load_png("./crab2.png");
	hole = mlx_load_png("./exit2.png");
	if (!sand || !plant || !shell || !crab || !hole)
		return (0);
	data->sand = get_background(data, sand);
	data->plant = get_image(data, plant);
	data->shell = get_image(data, shell);
	data->crab = get_image(data, crab);
	data->hole = get_image(data, hole);
	if (!data->sand || !data->plant || !data->shell || !data->crab || !data->hole)
		return (0);
	return (1);
}

mlx_image_t	*get_background(t_map_data *data, mlx_texture_t *texture)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(data->mlx, texture);
	if (!img || !mlx_resize_image(img, WIDTH * data->size->x, HEIGHT * data->size->y))
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

void my_keyhook(mlx_key_data_t keydata, void *mapdata)
{
	t_map_data *data;

	data = mapdata;
	if (data->crab->enabled == false)
	{
		mlx_close_window(data->mlx);
		return ;
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_left(data);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_up(data);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_right(data);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_down(data);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx);
		return ;
	}
}

void	move_left(t_map_data *data)
{
	if (data->map[data->player->y][data->player->x - 1] != '1')
			{
				data->player->x = data->player->x - 1;
				data->crab->instances->x = (data->player->x * WIDTH);
				if (data->id_map[data->player->y][data->player->x] >= 0)
				{
					data->shell->instances[data->id_map[data->player->y][data->player->x]].enabled = false;
					data->collectibles--;
				}
				else if (data->map[data->player->y][data->player->x] == 'E' && data->collectibles == 0)
				{
					data->crab->enabled = false;
				}
			}
}

void	move_up(t_map_data *data)
{
	if (data->map[data->player->y - 1][data->player->x] != '1')
			{
				data->player->y = data->player->y - 1;
				data->crab->instances->y = (data->player->y * WIDTH);
				if (data->id_map[data->player->y][data->player->x] >= 0)
				{
					data->shell->instances[data->id_map[data->player->y][data->player->x]].enabled = false;
					data->collectibles--;
				}
			}
}

void	move_right(t_map_data *data)
{
	if (data->map[data->player->y][data->player->x + 1] != '1')
			{
				data->player->x = data->player->x + 1;
				data->crab->instances->x = (data->player->x * HEIGHT);
				if (data->id_map[data->player->y][data->player->x] >= 0)
				{
					data->shell->instances[data->id_map[data->player->y][data->player->x]].enabled = false;
					data->collectibles--;
				}
			}
}

void	move_down(t_map_data *data)
{
	if (data->map[data->player->y + 1][data->player->x] != '1')
			{
				data->player->y = data->player->y + 1;
				data->crab->instances->y = (data->player->y * HEIGHT);
				if (data->id_map[data->player->y][data->player->x] >= 0)
				{
					data->shell->instances[data->id_map[data->player->y][data->player->x]].enabled = false;
					data->collectibles--;
				}
			}
}

char	**get_map(char **argv, char **map, t_map_data *data)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (!get_map_height(fd, data))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	map = malloc(sizeof(char *) * (data->size->y + 1));
	if (!map)
	{
		free(data->size);
		return (NULL);
	}
	while (i < data->size->y)
	{
		map[i++] = get_next_line(fd);
		if (map[i - 1] == NULL)
		{
			free(data->size);
			return (free_arr(map, i));
		}
	}
	map[i] = NULL;
	data->map = map;
	return (map);
}

size_t	get_map_height(int fd, t_map_data *data)
{
	char	*line;
	t_point	*size;

	size = ft_calloc(1, sizeof(t_point));
	if (!size)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		size->y++;
		free(line);
		line = get_next_line(fd);
	}
	data->size = size;
	return (size->y);
}

int	**get_id_map(t_map_data *data)
{
	int	i;

	i = 0;
	data->id_map = malloc(data->size->y * sizeof(int *));
	if (!data->id_map)
	{
		// free stuff
		return (NULL);
	}
	while (i < data->size->y)
	{
		data->id_map[i] = malloc(data->size->x * sizeof(int));
		if (!data->id_map[i])
		{
			// free stuff
			return (NULL);
		}
		i++;
	}
	fill_id_map(data);
	return (data->id_map);
}

void	fill_id_map(t_map_data *data)
{
	int y = 0;
	int x = 0;

	while (y < data->size->y)
	{
		while (x < data->size->x)
		{
			data->id_map[y][x] = -1;
			x++;
		}
		y++;
		x = 0;
	}
}

int	map_check(char **map, t_map_data *data)
{
	if (!component_check(map, data) || !shape_check(map, data) ||
		!path_check(map, data->player, data))
	{
		ft_printf("Invalid map\n");
		free_arr(map, data->size->y);
		free(data->size);
		free(data);
		return (0);
	}
	ft_printf("Valid map\n\n");
	return (1);
}

int	component_check(char **map, t_map_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (!ft_strchr("10PEC\n", map[y][x++]))
				return (0);
		}
		y++;
		x = 0;
	}
	if (!symbol_check(map, data, 'P') || 
		!symbol_check(map, data, 'E') ||
		!symbol_check(map, data, 'C'))
		return (0);
	return (1);
}

int	symbol_check(char **map, t_map_data *data, char symbol)
{
	int	count;

	count = count_symbols(map, data, symbol);
	if (count == -1)
		return (0);
	if ((symbol == 'P' || symbol == 'E') && (count != 1))
		return (0);
	if (symbol == 'C' && count < 1)
		return (0);
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
					if (!set_coordinates(data, y, x -1))
						return (-1);
				}
				count++;
			}
		}
		y++;
		x = 0;
	}
	return (count);
}

int	shape_check(char **map, t_map_data *data)
{
	int	y;

	y = 1;
	data->size->x = ft_strlen(map[0]);
	while (map[y])
	{
		if ((int)ft_strlen(map[y]) != data->size->x)
			return (0);
		y++;
	}
	if (!wall_check(map, data))
		return (0);
	data->size->x = data->size->x - 1;
	return (1);
}

int	wall_check(char **map, t_map_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = data->size->y;
	while (map[y - 1][x])
	{
		if (!ft_strchr("1\n", map[y - 1][x++]))
			return (0);
	}
	while (y > 0)
	{
		y--;
		if (map[y][0] != '1' || map[y][data->size->x - 2] != '1')
			return (0);
	}
	x = 0;
	while (map[0][x])
	{
		if (!ft_strchr("1\n", map[0][x++]))
			return (0);
	}
	return (1);
}

int	path_check(char **map, t_point *player, t_map_data *data)
{
	int i;
	char **copy;

	i = 0;
	copy = malloc(sizeof(char *) * (data->size->y + 1));
	if (!copy)
	{
		free_arr(map, data->size->y);
		free(data->size);
		free(data->size);
		free(data);
		return (-1);
	}
	while (i < data->size->y)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_arr(copy, i);
			return (0);
		}
		i++;
	}
	fill_map(copy, *player);
	if (count_symbols(copy, data, 'C') || count_symbols(copy, data, 'E'))
	{
		free_arr(copy, i);
		return (0);
	}
	free_arr(copy, i);
	return (1);
}

void	fill_map(char **map, t_point curr)
{
	if (map[curr.y][curr.x] == '1')
		return ;
	map[curr.y][curr.x] = '1';
	fill_map(map, (t_point){curr.y - 1, curr.x});
	fill_map(map, (t_point){curr.y + 1, curr.x});
	fill_map(map, (t_point){curr.y, curr.x - 1});
	fill_map(map, (t_point){curr.y, curr.x + 1});
}

int	set_coordinates(t_map_data *data, int y, int x)
{
	t_point *coordinates;

	coordinates = malloc(sizeof(t_point));
	if (!coordinates)
		return (0);
	coordinates->y = y;
	coordinates->x = x;
	data->player = coordinates;
	return (1);
}

int	free_data(t_map_data *data)
{
	free_arr(data->map, data->size->y);
	free(data->size);
	free(data->player);
	free(data);
	return (0);
}