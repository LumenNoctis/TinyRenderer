/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:56:20 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 05:46:11 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <fcntl.h>
#include <stdio.h>

t_coordinates	**parse_even(char **map, int len, int size)
{
	t_coordinates	**coords;
	int				i;
	float			x;
	float			y;

	i = 0;
	x = (len / 2) - 0.5;
	y = (size / len) / 2;
	coords = malloc(sizeof(t_coordinates*) * size + 1);
	while (i < size)
	{
		coords[i] = malloc(sizeof(t_coordinates));
		coords[i]->x = x;
		coords[i]->y = y;
		coords[i]->z = ft_atoi(map[i]);
		i++;
		if (x == -1 * ((len / 2) - 0.5))
		{
			y--;
			x = (len / 2) - 0.5;
		}
		else
			x--;
	}
	return (coords);
}

t_coordinates	**parse_odd(char **map, int len, int size)
{
	t_coordinates	**coords;
	int				i;
	float			x;
	float			y;

	i = 0;
	x = (len / 2);
	y = (size / len) / 2;
	coords = malloc(sizeof(t_coordinates*) * size + 1);
	while (i < size)
	{
		coords[i] = malloc(sizeof(t_coordinates));
		coords[i]->x = x;
		coords[i]->y = y;
		coords[i]->z = ft_atoi(map[i]);
		i++;
		if (x == -1 * (len / 2))
		{
			y--;
			x = (len / 2);
		}
		else
			x--;
	}
	return (coords);
}

void			parse_file(char **map, int len)
{
	t_coordinates	**coords;
	int				size;
	int				i;

	i = 0;
	size = ft_strarrlen(map);
	if (len % 2 == 0)
		coords = parse_even(map, len, size);
	else
		coords = parse_odd(map, len, size);
	while (i <= size - 1)
	{
		free(map[i]);
		i++;
	}
	free(map);
	mlx_prgr(coords, size, len);
}
