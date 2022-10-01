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

Vector3F_t		RotateVertex(Vector3F_t vertex, Vector3_t center, Vector3F_t rotation)
{
	Vector3F_t result;
	int px;
	int py;
	int pz;
	float rx;
	float ry;
	float rz;

	static int z_scale;
	static int z_inc = 0.1;
	Vector3F_t axisx = {-250,0,0};
	Vector3F_t axisy = {0,-250,0};
	Vector3F_t axisz = {0,0,250};
	Vector3F_t raxisx;
	Vector3F_t raxisy;
	Vector3F_t raxisz;

	Vector3F_t taxisx;
	Vector3F_t taxisy;
	Vector3F_t taxisz;


	raxisx = axisx;
	raxisy = axisy;
	raxisz = axisz;

	taxisx = axisx;
	taxisy = axisy;
	taxisz = axisz;

	px = vertex.x - center.x;
	py = vertex.y - center.y;
	pz = vertex.z - center.z;

	rx = ToRad(rotation.x);
	ry = ToRad(rotation.y);
	rz = ToRad(rotation.z);

	result.x = vertex.x;
	result.y = vertex.y;
	result.z = vertex.z * 0.1;

	float z = vertex.z * 0.1;
	// result.y = (cos(rx) * result.y) - (sin(rx) * result.z);
	// result.z = (sin(rx) * vertex.y) + (cos(rx) * result.z);
	// result.x = (cos(ry) * result.x) + (sin(ry) * result.z);


	result.x = (cos(ry) * (vertex.x)) - (sin(ry) * (vertex.y));
	result.y = (sin(ry) * (vertex.x)) + (cos(ry) * (vertex.y));
	result.z = result.z;

	result.x = (cos(rx) * (result.x)) + (sin(rx) * (z));
	result.y = result.y;
	result.z = (sin(rx) * (result.x)) + (cos(rx) * (z));

	// axisx.y = (cos(rx) * axisx.y) - (sin(rx) * axisx.z);
	// axisx.z = (sin(rx) * raxisx.y) + (cos(rx) * axisx.z);
	// axisx.x = (cos(ry) * axisx.x) + (sin(ry) * axisx.z);

	// axisy.y = (cos(rx) * axisy.y) - (sin(rx) * axisy.z);
	// axisy.z = (sin(rx) * raxisy.y) + (cos(rx) * axisy.z);
	// axisy.x = (cos(ry) * axisy.x) + (sin(ry) * axisy.z);

	// axisz.y = (cos(rx) * axisz.y) - (sin(rx) * axisz.z);
	// axisz.z = (sin(rx) * raxisz.y) + (cos(rx) * axisz.z);
	// axisz.x = (cos(ry) * axisz.x) + (sin(ry) * axisx.z);




	SDLX_Display *display;

	display= SDLX_DisplayGet();

	// SDL_SetRenderDrawColor(display->renderer, 0xFF, 0x00, 0x00, 0xFF);
	// SDL_RenderDrawLine(display->renderer, 250, 250, (display->win_w / 2) - axisx.x, (display->win_w / 2) - axisx.y );
	// SDL_SetRenderDrawColor(display->renderer, 0x00, 0xFF, 0x00, 0xFF);
	// SDL_RenderDrawLine(display->renderer, 250, 250, (display->win_w / 2) - axisy.x, (display->win_w / 2) - axisy.y);
	// SDL_SetRenderDrawColor(display->renderer, 0x00, 0x00, 0xFF, 0xFF);
	// SDL_RenderDrawLine(display->renderer, 250, 250, (display->win_w / 2) - axisz.x, (display->win_w / 2) - axisz.y);

	// SDL_Log("y %f z %f mult %f %f",raxisx.y , taxisx.z, raxisx.y * taxisx.z,  (display->win_w / 2) - (raxisx.y * taxisx.z));
	// SDL_SetRenderDrawColor(display->renderer, 0xFF, 0xFF, 0x00, 0xFF);
	// SDL_RenderDrawLine(display->renderer, 250, 250, (display->win_w / 2) - raxisx.x, (display->win_w / 2) - (raxisx.y * taxisx.z) );
	// SDL_SetRenderDrawColor(display->renderer, 0x00, 0xFF, 0xFF, 0xFF);
	// SDL_RenderDrawLine(display->renderer, 250, 250, (display->win_w / 2) - raxisy.x, (display->win_w / 2) - (raxisy.y * taxisy.z ));
	// SDL_SetRenderDrawColor(display->renderer, 0xFF, 0x00, 0xFF, 0xFF);
	// SDL_RenderDrawLine(display->renderer, 250, 250, (display->win_w / 2) - raxisz.x, (display->win_w / 2) - (raxisz.y * taxisz.z ));

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

Vector3F_t		ScaleVertex(Vector3_t vertex, float scale)
{
	Vector3F_t result;

	result.x = (float)(vertex.x) * scale;
	result.y = (float)(vertex.y) * scale;
	result.z = (float)(vertex.z) * scale;

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
