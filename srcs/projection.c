/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:06:47 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 05:48:59 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <math.h>
#include "../incl/colors.h"

static void		rotate_x(t_coordinates *pt, float angle, float (*coord_2d)[])
{
	angle = (angle) * (M_PI / 180);
	(*coord_2d)[1] = cos(angle) * (pt->n_y);
}

static void		rotate_y(t_coordinates *pt, float angle, float (*coord_2d)[])
{
	angle = (angle) * (M_PI / 180);
	(*coord_2d)[0] = cos(angle) * (pt->n_x);
}

static void		rotate_z(t_coordinates *pt, float angle, float (*coord_2d)[])
{
	angle = (angle) * (M_PI / 180);
	(*coord_2d)[0] = cos(angle) * pt->x - sin(angle) * pt->y;
	(*coord_2d)[1] = sin(angle) * pt->x + cos(angle) * pt->y;
}

void			window_init(t_data *data)
{
	int		i;
	float	c2d[2];
	char	*str;

	i = 0;
	str = ((data->mode == 0) ? "--\n| View |--" : "--\n| Edit |\n--");
	mlx_string_put(data->ptr, data->window, (data->win_len / 1.5),
			data->win_h / 10, ORANGE, str);
	if (data->mode == 1)
		mlx_string_put(data->ptr, data->window, (data->win_len / 1.8),
				(data->win_h / 10) + 30, GREEN, "Press Space to save");
	while (i < data->size)
	{
		rotate_z((*data->coords)[i], data->a_z, &c2d);
		(*data->coords)[i]->n_x = c2d[0];
		(*data->coords)[i]->n_y = c2d[1];
		rotate_x((*data->coords)[i], data->a_x, &c2d);
		rotate_y((*data->coords)[i], 30, &c2d);
		(*data->coords)[i]->n_x = data->win_len / 2 - (c2d[0] * data->scale);
		(*data->coords)[i]->n_y = data->win_h / 2 - (c2d[1] * data->scale)
		- ((*data->coords)[i]->z * data->scale / 16);
		i++;
	}
	make_image(data, 0);
	ft_memset(c2d, 0, 2);
}

void			scale(t_data **data, int ud)
{
	if (ud == 0)
		(*data)->scale += 1;
	else
		(*data)->scale -= 1;
	mlx_clear_window((*data)->ptr, (*data)->window);
	window_init(*data);
}
