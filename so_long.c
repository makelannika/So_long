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
	ft_printf("height: %d width: %d\n", HEIGHT, WIDTH);
	if (!map_check(map, data))
		return (0);
	ft_printf("map width: %d\n", data->size->x);
	ft_printf("map height: %d\n", data->size->y);
	ft_printf("collectibles: %d\n", data->collectibles);
	ft_printf("\n");
	while (map[i])
		ft_printf("%s", map[i++]);
	ft_printf("\n");
	ft_printf("player's coordinates y: %d x: %d\n", data->player->y, data->player->x);
	ft_printf("exit's coordinates y: %d x: %d\n\n", data->exit->y, data->exit->x);
	so_long(data);
	free_arr(map, data->size->y);
	free_data(data);
	return (0);
}

int	so_long(t_map_data *data)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*sand;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH * data->size->x, HEIGHT * data->size->y, "So_long", true);
	if (!mlx)
		return(0);
	data->mlx = mlx;
	sand = mlx_load_png("./sand.png");
	get_textures(data);
	img = mlx_texture_to_image(data->mlx, sand);
	if (!img)
		return (0);
	mlx_resize_image(img, WIDTH * data->size->x, HEIGHT * data->size->y);
	if (mlx_image_to_window(data->mlx, img, 0, 0 < 0))
		return(0);
	draw_map(data);
	mlx_key_hook(mlx, &my_keyhook, data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}

int	draw_map(t_map_data *data)
{
	int	y = 0;
	int	x = 0;
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
				if (mlx_image_to_window(data->mlx, data->shell, x * WIDTH, y * HEIGHT) < 0)
					return(0);
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
	mlx_texture_t	*plant;
	mlx_texture_t	*shell;
	mlx_texture_t	*crab;
	mlx_texture_t	*hole;

	plant = mlx_load_png("./plant.png");
	data->plant = get_image(data, plant);
	shell = mlx_load_png("./shell5.png");
	data->shell = get_image(data, shell);
	crab = mlx_load_png("./crab2.png");
	data->crab = get_image(data, crab);
	hole = mlx_load_png("./exit2.png");
	data->hole = get_image(data, hole);
	return (1);
}

mlx_image_t	*get_image(t_map_data *data, mlx_texture_t *texture)
{
	mlx_image_t		*img;

	img = mlx_texture_to_image(data->mlx, texture);
	mlx_resize_image(img, WIDTH, HEIGHT);
	if (!img)
	return (NULL);
	return (img);
}

void my_keyhook(mlx_key_data_t keydata, void *data)
{
	t_map_data *mdata;

	mdata = data;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		{
			if (mdata->map[mdata->player->y][mdata->player->x - 1] != '1')
			{
			mdata->player->x = mdata->player->x - 1;
			mdata->crab->instances->x = (mdata->player->x * WIDTH);
			}
		}
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		{
			if (mdata->map[mdata->player->y - 1][mdata->player->x] != '1')
			{
			mdata->player->y = mdata->player->y - 1;
			mdata->crab->instances->y = (mdata->player->y * WIDTH);
			}
		}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		{
			if (mdata->map[mdata->player->y][mdata->player->x + 1] != '1')
			{
			mdata->player->x = mdata->player->x + 1;
			mdata->crab->instances->x = (mdata->player->x * HEIGHT);
			}
		}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		{
			if (mdata->map[mdata->player->y + 1][mdata->player->x] != '1')
			{
			mdata->player->y = mdata->player->y + 1;
			mdata->crab->instances->y = (mdata->player->y * HEIGHT);
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
	{
		ft_printf("player or exit != 1");
		return (0);
	}
	if (symbol == 'C' && count < 1)
	{
		ft_printf("no collectibles\n");
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
				if (symbol == 'P' || symbol == 'E')
				{
					if (!set_coordinates(data, symbol, y, x -1))
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

int	set_coordinates(t_map_data *data, char symbol, int y, int x)
{
	t_point *coordinates;

	coordinates = malloc(sizeof(t_point));
	if (!coordinates)
		return (0);
	coordinates->y = y;
	coordinates->x = x;
	if (symbol == 'P')
		data->player = coordinates;
	else if (symbol == 'E')
		data->exit = coordinates;
	return (1);
}

int	free_data(t_map_data *data)
{
	free(data->size);
	free(data->player);
	free(data->exit);
	free(data);
	return (0);
}