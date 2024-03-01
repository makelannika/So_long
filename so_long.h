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

typedef struct s_map
{
	size_t	width;
	int		height;
	int		collectibles;
}	t_map;

char	**get_map(char **argv, char **map, t_map *stats);
size_t	get_map_height(int fd, t_map *stats);
int		map_check(char **map, t_map *stats);
int		component_check(char **map, t_map *stats);
int		shape_check(char **map, t_map *stats);
int		wall_check(char **map, t_map *stats);
int		count_symbols(char **map, char symbol);

#endif
