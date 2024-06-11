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
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define HEIGHT 90
# define WIDTH 90

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_map_data
{
	t_point			size;
	t_point			player;
	int				collectibles;
	char			**map;
	int				**id_map;
	mlx_t			*mlx;
	mlx_texture_t	*background_txtr;
	mlx_texture_t	*wall_txtr;
	mlx_texture_t	*collectible_txtr;
	mlx_texture_t	*player_txtr;
	mlx_texture_t	*exit_txtr;
	mlx_image_t		*b;
	mlx_image_t		*w;
	mlx_image_t		*c;
	mlx_image_t		*p;
	mlx_image_t		*e;
	int				moves;
}	t_map_data;

char		**get_map(char **argv, t_map_data *data);
int			**get_id_map(t_map_data *data);
int			map_check(t_map_data *data);
int			shape_check(t_map_data *data);
int			symbol_check(t_map_data *data, char symbol);
int			count_symbols(char **map, t_map_data *data, char symbol);
int			path_check(t_point player, t_map_data *data);
int			get_textures(t_map_data *data);
int			draw_map(t_map_data *data);
void		movement(mlx_key_data_t keydata, void *mapdata);
void		delete_textures(t_map_data *data);
void		free_id_map(int	**id_map, int j);

#endif
