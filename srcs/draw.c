#include "renderer.h"

void DrawVertices(char *pixels, char *z_buffer, Mesh_t mesh, SDLX_Display *display)
{
	Vector2_t screenCoord;
	int pixelsBound;

	pixelsBound = display->win_h * display->win_w;

	int i = 0;
	for (int i = 0; i < mesh.vertexCount; i++)
	{
		screenCoord = (Vector2_t){mesh.vertices[i].screenCoord.x, mesh.vertices[i].screenCoord.y};
		if (display->win_w * screenCoord.y + screenCoord.x < pixelsBound &&
			display->win_w * screenCoord.y + screenCoord.x >= 0)
		{
			uint32_t *t = (uint32_t *)pixels;
			t[display->win_w * screenCoord.y + screenCoord.x] = 0xFF0000FF;
			// z_buffer[screenCoord.x * screenCoord.y] = mesh.vertices[i].coordinates.z;
		}
	}
}

void DrawEdges(char *pixels, char *z_buffer, Mesh_t mesh, SDLX_Display *display)
{
	Vector2F_t screenCoordA;
	Vector2F_t screenCoordB;
	int pixelsBound;

	pixelsBound = display->win_h * display->win_w;

	SDL_SetRenderDrawColor(display->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	for (int i = 0; i < mesh.edgesCount; i++)
	{
		screenCoordA = mesh.edges[i].vertexA->screenCoord;
		screenCoordB = mesh.edges[i].vertexB->screenCoord;
		SDL_RenderDrawLine(display->renderer, screenCoordA.x, screenCoordA.y, screenCoordB.x, screenCoordB.y);
	}
	SDL_SetRenderDrawColor(display->renderer, 0x00, 0x00, 0x00, 0x00 );
}

void DrawMesh(RenderContext_t *ctx)
{
	Vertex_t toScreen;
	SDL_Surface *surf;
	SDL_Texture	*texture;



	memset(ctx->pixels, 0x000000, ctx->display->win_h * ctx->display->win_w * PIXEL_CHANNELS * 2);

	DrawVertices(ctx->pixels, NULL, ctx->mesh, ctx->display);
	DrawEdges(ctx->pixels, ctx->z_buffer, ctx->mesh, ctx->display);

	texture = SDL_CreateTextureFromSurface(ctx->display->renderer, ctx->surface);
	SDL_RenderCopy(ctx->display->renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}
