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

# include "renderer_structs.h"

RenderContext_t *initRenderContext(void);
void	DrawMesh(RenderContext_t *ctx);
void	TransformMesh(Mesh_t *mesh);
void	HandleInput(RenderContext_t *ctx);
int		count (char *str, char c);
char	*OpenFile(char *filename, long *filesize);
void	MapToMesh(Mesh_t *dest, char *filename);


void printCoord3D(Vector3_t coord);
void printCoord3DF(Vector3F_t coord);
void printCoord2D(Vector2_t coord);

#endif
