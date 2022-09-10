/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:01:25 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 03:35:59 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "../incl/colors.h"
#include "../incl/keys.h"

void	move_pixel(t_data **data, int key)
{
	if (key == K_W)
		(*(*data)->coords)[(*data)->i]->z += 1;
	if (key == K_S)
		(*(*data)->coords)[(*data)->i]->z -= 1;
	if (key == K_A)
		(*(*data)->coords)[(*data)->i]->x -= 1;
	if (key == K_D)
		(*(*data)->coords)[(*data)->i]->x += 1;
}

void	select_lr(t_data **data, int key)
{
	if (key == K_RIGHT)
	{
		(*data)->i += 1;
		if ((*data)->i == (*data)->size)
			(*data)->i = 0;
	}
	if (key == K_LEFT)
	{
		(*data)->i -= 1;
		if ((*data)->i < 0)
			(*data)->i = (*data)->size - 1;
	}
}

void	select_ud(t_data **data, int key)
{
	if (key == K_DOWN)
	{
		if ((*data)->i + (*data)->len < (*data)->size)
			(*data)->i += (*data)->len;
	}
	if (key == K_UP)
	{
		if (((*data)->i - (*data)->len) >= 0)
			(*data)->i -= (*data)->len;
	}
}
