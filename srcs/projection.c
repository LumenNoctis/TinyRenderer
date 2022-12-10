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

# define X px
# define Y py
# define Z pz

double		ToRad(double angle)
{
	double result;

	result = angle * M_PI;
	result /= 180;

	return result;
}

Vector3F_t		RotateVertex(Vector3F_t vertex, Vector3F_t center, Vector3F_t rotation)
{
	Vector3F_t result;
	double px;
	double py;
	double pz;
	double rx;
	double ry;
	double rz;

	px = vertex.x - center.x;
	py = vertex.y - center.y;
	pz = vertex.z - center.z;

	rx = ToRad(rotation.x);
	ry = ToRad(rotation.y);
	rz = ToRad(rotation.z);

	result.x = vertex.x;
	result.y = vertex.y;
	result.z = vertex.z;

	result.x = (cos(rx) * (px)) - (sin(rx) * (py));

	result.x = (cos(ry) * result.x) + (sin(ry) * (result.z));
	result.y = (sin(rx) * (px)) + (cos(rx) * (py));
	result.z = (-cos(ry) * result.y) + (sin(ry) * (result.z));

	return  result;
}

Vector2F_t CoordToScreen(Vector3F_t in, float scale)
{
	SDLX_Display *display;
	Vector2F_t out;

	display = SDLX_DisplayGet();
	out.x = in.x + (display->win_w / 2);
	out.y = in.y + (display->win_h / 2);

	return out;
}

Vector3F_t		ScaleVertex(Vector3F_t vertex, float scale)
{
	Vector3F_t result;

	result.x = vertex.x * scale;
	result.y = vertex.y * scale;
	result.z = vertex.z * scale;

	return result;
}

Vector3_t		TranslateVertex(Vector3_t vertex, Vector3_t center, Vector3_t translation)
{

}

void		TransformMesh(Mesh_t *mesh)
{
	int i;
	Vector3F_t	coordinates;

	i = 0;
	for (i; i < mesh->vertexCount; i++)
	{
		coordinates = ScaleVertex(mesh->vertices[i].coordinates, mesh->scale);
		coordinates = RotateVertex(coordinates, *(mesh->center), mesh->rotation);
		mesh->vertices[i].screenCoord = CoordToScreen(coordinates, mesh->scale);
	}
}
