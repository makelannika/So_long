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

# define HEIGHT 90
# define WIDTH 90

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_map_data
{
	t_point			*size;
	t_point			*player;
	int				collectibles;
	char			**map;
	int				**id_map;
	mlx_t			*mlx;
	mlx_texture_t	*sand_t;
	mlx_texture_t	*plant_t;
	mlx_texture_t	*shell_t;
	mlx_texture_t	*crab_t;
	mlx_texture_t	*hole_t;
	mlx_image_t		*sand;
	mlx_image_t		*plant;
	mlx_image_t		*shell;
	mlx_image_t		*crab;
	mlx_image_t		*hole;
	int				moves;
}	t_map_data;

int			check_extension(char *arg);
char		**get_map(char **argv, t_map_data *data);
void		get_map_height(int fd, t_map_data *data, int *flag);
int			**get_id_map(t_map_data *data);
void		fill_id_map(t_map_data *data);
int			map_check(t_map_data *data);
int			component_check(t_map_data *data);
int			shape_check(t_map_data *data);
int			wall_check(t_map_data *data);
int			symbol_check(t_map_data *data, char symbol);
int			count_symbols(char **map, t_map_data *data, char symbol);
int			set_coordinates(t_map_data *data, int y, int x);
int			path_check(t_point *player, t_map_data *data);
char		**get_copy(char **copy, t_map_data *data);
void		fill_map(char **map, t_point curr);
int			so_long(t_map_data *data);
int			free_data(t_map_data *data);
int			get_textures(t_map_data *data);
mlx_image_t	*get_image(t_map_data *data, mlx_texture_t *texture);
mlx_image_t	*get_background(t_map_data *data, mlx_texture_t *texture);
int			draw_map(t_map_data *data);
int			draw_row(t_map_data *data, int y);
void		my_keyhook(mlx_key_data_t keydata, void *mapdata);
void		move_left(t_map_data *mdata, int y, int x);
void		move_up(t_map_data *mdata, int y, int x);
void		move_right(t_map_data *mdata, int y, int x);
void		move_down(t_map_data *mdata, int y, int x);
void		delete_textures(t_map_data *data);
void		free_id_map(int	**id_map, int j);
void		copy_map(t_map_data *data, int fd, int *flag);

#endif
