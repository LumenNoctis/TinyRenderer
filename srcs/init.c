#include "renderer.h"

void initMesh(RenderContext_t *ctx)
{
	ctx->mesh.vertices[0].coordinates.x = -10;
	ctx->mesh.vertices[0].coordinates.y = 10;
	ctx->mesh.vertices[0].coordinates.z = 0;

	ctx->mesh.vertices[1].coordinates.x = 10;
	ctx->mesh.vertices[1].coordinates.y = 10;
	ctx->mesh.vertices[1].coordinates.z = 0;

	ctx->mesh.vertices[2].coordinates.x = -10;
	ctx->mesh.vertices[2].coordinates.y = -10;
	ctx->mesh.vertices[2].coordinates.z = 0;

	ctx->mesh.vertices[3].coordinates.x = 10;
	ctx->mesh.vertices[3].coordinates.y = -10;
	ctx->mesh.vertices[3].coordinates.z = 0;

	ctx->mesh.edges[0].vertexA = &ctx->mesh.vertices[0];
	ctx->mesh.edges[0].vertexA = &ctx->mesh.vertices[1];

	ctx->mesh.edges[1].vertexA = &ctx->mesh.vertices[1];
	ctx->mesh.edges[1].vertexA = &ctx->mesh.vertices[2];

	ctx->mesh.edges[2].vertexA = &ctx->mesh.vertices[2];
	ctx->mesh.edges[2].vertexA = &ctx->mesh.vertices[3];

	ctx->mesh.edges[3].vertexA = &ctx->mesh.vertices[3];
	ctx->mesh.edges[3].vertexA = &ctx->mesh.vertices[0];

}


RenderContext_t *initRenderContext(void)
{
	RenderContext_t *ctx;

	SDLX_InitDefault();

	ctx = SDL_calloc(1, sizeof(*ctx));
	ctx->display = SDLX_DisplayGet();
	ctx->mode = MODE_VIEW;
	ctx->scale = 1;

	ctx->mesh.vertexCount = 4;
	ctx->mesh.edgesCount = 4;
	ctx->mesh.vertices = calloc(ctx->mesh.vertexCount, sizeof(Vertex_t));
	ctx->mesh.edges = calloc(ctx->mesh.edgesCount, sizeof(Edge_t));

	initMesh(ctx);

	ctx->pixels = calloc(ctx->display->win_h * ctx->display->win_w * 2, sizeof(uint32_t));
	ctx->z_buffer = ctx->pixels + (ctx->display->win_h * ctx->display->win_w);

	ctx->surface = SDL_CreateRGBSurfaceFrom(
		ctx->pixels,
		ctx->display->win_w,
		ctx->display->win_h,
		PIXEL_CHANNELS * 8,
		ctx->display->win_w * PIXEL_CHANNELS,
		*((Uint32 *)(&(SDL_Color){.r = 255, .g = 000, .b = 000, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 255, .b = 000, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 000, .b = 255, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 000, .b = 000, .a = 255}))
		);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_LEFT);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_LEFT);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_RIGHT);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_RIGHT);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_UP);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_UP);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_DOWN);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_DOWN);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_ZOOM);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_MODE);

	return ctx;
}
