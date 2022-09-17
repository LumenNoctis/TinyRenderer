#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include "SDLX/SDLX.h"
# include "MT/MT.h"

# define MODE_VIEW 0
# define MODE_EDIT 1

# define PIXEL_CHANNELS 4

enum {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_ZOOM,
	KEY_MODE
};

typedef struct Vector2
{
	int x;
	int y;
}				Vector2_t;

typedef struct Vector3
{
	int x;
	int y;
	int z;
}				Vector3_t;

typedef struct		s_vertex
{
	Vector3_t		coordinates;
	uint32_t		color;
}					Vertex_t;


typedef struct		s_edge
{
	Vertex_t		*vertexA;
	Vertex_t		*vertexB;
}					Edge_t;

typedef struct		s_mesh
{
	int				vertexCount;
	int				edgesCount;

	Vector3_t		rotation;
	Vector3_t		*center;
	Vector3_t		_center;
	Vertex_t		*vertices;
	Edge_t			*edges;
}					Mesh_t;

typedef struct		s_camera
{
	int				scale;
	Vector3_t		position;
}					Camera_t;

typedef struct		s_renderContext
{
	int				i;
	int				mode;
	int				a_z;
	int				a_x;

	float			scale;

	Mesh_t			mesh;
	SDLX_Display	*display;
	SDL_Surface		*surface;
	char 			*pixels;
	char			*z_buffer;
}					RenderContext_t;

#endif
