/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:28:53 by amakela           #+#    #+#             */
/*   Updated: 2024/02/22 18:28:55 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_map
{
	t_point	*size;
	t_point	*player;
	t_point	*exit;
	int		collectibles;
}	t_map;

char	**get_map(char **argv, char **map, t_map *data);
size_t	get_map_height(int fd, t_map *data);
int		map_check(char **map, t_map *data);
int		component_check(char **map, t_map *data);
int		shape_check(char **map, t_map *data);
int		wall_check(char **map, t_map *data);
int		symbol_check(char **map, t_map *data, char symbol);
int		count_symbols(char **map, t_map *data, char symbol);
int		set_coordinates(t_map *data, char symbol, int y, int x);
int		path_check(char **map, t_point *player, t_map *data);
void	fill_map(char **map, t_point curr);

#endif
