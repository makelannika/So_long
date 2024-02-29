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


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <MLX42/MLX42.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;
	int		line_count;
	char	**map;

	i = 0;
	line_count = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
		line_count++;
	close(fd);
	fd = open(argv[1], O_RDONLY);
	map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (0);
	while ((line = get_next_line(fd)))
		map[i++] = line;
	map[i] = NULL;
	i = 0;
	while (map[i])
		ft_printf("%s", map[i++]);
	return (0);
}