#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include "SDLX/SDLX.h"
# include "MT/MT.h"

enum {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_ZOOM,
	KEY_MODE
};


typedef struct		s_edge
{
	MT_Vector3		*vertexA;
	MT_Vector3		*vertexB;
}					Edge_t;

typedef struct		s_mesh
{
	int				verticesArrLen;
	int				verticesArrCount;

	MT_Vector3		**vertices;
	Edge_t			*edges;
}					Mesh_t;

typedef struct		s_renderContext
{
	int				i;
	int				mode;
	int				a_z;
	int				a_x;

	float			scale;

	SDLX_Display	*display;
}					RenderContext_t;

#endif
