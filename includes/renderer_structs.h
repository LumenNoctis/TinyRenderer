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
	KEY_RESET,
	KEY_MODE,
	KEY_TRACE,
	KEY_SHIFT,
	KEY_ZOOMU,
	KEY_ZOOMD
};

typedef struct Vector2
{
	int x;
	int y;
}				Vector2_t;

typedef struct Vector2F
{
	double x;
	double y;
}				Vector2F_t;

typedef struct Vector3
{
	int x;
	int y;
	int z;
}				Vector3_t;

typedef struct Vector3F
{
	double x;
	double y;
	double z;
}				Vector3F_t;

typedef struct		s_vertex
{
	Vector3F_t		coordinates;
	Vector2F_t		screenCoord;
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

	double			scale;

	Vector3F_t		rotation;
	Vector3F_t		*center;
	Vector3F_t		_center;
	Vertex_t		*vertices;
	Edge_t			*edges;
}					Mesh_t;

typedef struct		s_camera
{
	int				scale;
	Vector3_t		position;
}					Camera_t;

typedef	struct		s_settings
{
	int				trace;
	int				mode;
}					Settings_t;

typedef struct		s_MeshRender
{
	char 			*pixels;
	char 			*trace;
	char			*z_buffer;

	SDL_Surface		*pixelSurf;
	SDL_Surface		*traceSurf;
}					MeshRender_t;

typedef struct		s_renderContext
{
	Mesh_t			mesh;
	Settings_t		settings;
	MeshRender_t	render;

	SDLX_Display	*display;
	SDL_Texture		*menu;
	int				displayMenu;
}					RenderContext_t;

#endif
