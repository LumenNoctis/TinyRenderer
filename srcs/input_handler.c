/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:40:34 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 03:38:44 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "../incl/keys.h"
#include "../incl/colors.h"

void	data_init(t_data **data, int size, int len)
{
	(*data)->scale = 16;
	(*data)->size = size;
	(*data)->len = len;
	(*data)->mode = 0;
	(*data)->i = 0;
	(*data)->a_x = 50;
	(*data)->a_z = 45;
	if ((((size / len) + (size / len) / 2) * 10) < 500)
		(*data)->win_h = 500;
	else if (((size / len) + (size / len) / 2) * 10 > 1000)
		(*data)->win_h = 1000;
	else
		(*data)->win_h = ((size / len) + (size / len) / 2) * 10;
	if ((len + len / 2) * 16 < 500)
		(*data)->win_len = 500;
	else if ((len + len / 2) * 16 > 1000)
		(*data)->win_len = 1000;
	else
		(*data)->win_len = (len + len / 2) * 16;
}

int		on_key(int key, t_data **data)
{
	if (key == K_ESC)
	{
		mlx_destroy_window((*data)->ptr, (*data)->window);
		free_n_exit(*data);
	}
	else if (key == K_RETURN)
	{
		(*data)->mode = ((*data)->mode == 0) ? 1 : 0;
		mlx_clear_window((*data)->ptr, (*data)->window);
		window_init(*data);
	}
	else if (key == K_SPACE)
	{
		create_file(*data);
	}
	else
		(mode_func(data, key));
	return (1);
}

int		on_mouse(int key, int x, int y, t_data **data)
{
	x += 0;
	y += 0;
	if (key == K_SCROLL_U)
		scale(data, 0);
	if (key == K_SCROLL_D)
		scale(data, 1);
	return (1);
}

int		mlx_prgr(t_coordinates **coords, int size, int len)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data_init(&data, size, len);
	data->coords = &coords;
	data->ptr = mlx_init();
	data->window = mlx_new_window(data->ptr, data->win_len, data->win_h, "fdf");
	mlx_key_hook(data->window, on_key, &data);
	mlx_mouse_hook(data->window, on_mouse, &data);
	window_init(data);
	mlx_loop(data->ptr);
	return (0);
}
