/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:56:04 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 05:45:28 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "SDLX/SDLX.h"
# include "MT/MT.h"


typedef struct		s_edge
{
	MT_Vector3		*vertexA;
	MT_Vector3		*vertexB;
}					Edge_t;

typedef struct		s_mesh
{
	MT_Vector3		**vertices;
	Edge_t			*edges;


	int				verticesArrLen;
	int				verticesArrCount;

}					Mesh_t;

typedef struct		s_renderContext
{
	SDLX_Display	*display;
	float			scale;

	int				i;
	int				mode;
	int				a_z;
	int				a_x;
}					RenderContext_t;



void				window_init(t_data *data);
void				scale(t_data **data, int ud);
void				draw_square(float x, float y, t_data *data);

int					reader(char *file);
void				parse_file(char **map, int len);

int					make_image(t_data *data, int i);

int					write_error(int flag);
char				**error_loop(char *arg, int *len);

int					edit_file(char *arg);

void				mode_func(t_data **data, int key);

void				move_pixel(t_data **data, int key);
void				select_lr(t_data **data, int key);
void				select_ud(t_data **data, int key);

void				create_file(t_data *data);
void				free_n_exit(t_data *data);



#endif
