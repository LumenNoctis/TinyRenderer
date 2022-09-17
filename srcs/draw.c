#include "renderer.h"

void RenderLine()
{

}

Vector2_t CoordToScreen(Vector3_t in)
{
	SDLX_Display *display;
	Vector2_t out;

	display = SDLX_DisplayGet();
	out.x = in.x + (display->win_w / 2);
	out.y = in.y + (display->win_h / 2);

	return out;
}

void DrawVertices(char *pixels, char *z_buffer, Mesh_t mesh, SDLX_Display *display)
{
	Vector2_t screenCoord;
	int pixelsBound;

	pixelsBound = display->win_h * display->win_w;

	for (int i = 0; i < mesh.vertexCount; i++)
	{
		screenCoord = CoordToScreen(mesh.vertices[i].coordinates);
		if (screenCoord.x * screenCoord.y < pixelsBound)
		{
			// ((int *)pixels)[screenCoord.x * screenCoord.y] = mesh.vertices[i].color;
			// SDL_Log("x %d y %d", screenCoord.x, screenCoord.y);
			uint32_t *t = (uint32_t *)pixels;
			t[display->win_w * screenCoord.y + screenCoord.x] = 0xFF0000FF;
			// z_buffer[screenCoord.x * screenCoord.y] = mesh.vertices[i].coordinates.z;
		}
	}
}

void DrawEdges()
{

}

void DrawMesh(RenderContext_t *ctx)
{
	Vertex_t toScreen;
	SDL_Surface *surf;
	SDL_Texture	*texture;

	memset(ctx->pixels, 0x000000, ctx->display->win_h * ctx->display->win_w * PIXEL_CHANNELS * 2);

	DrawVertices(ctx->pixels, ctx->z_buffer, ctx->mesh, ctx->display);
	// for (int edges = 0; edges < ctx->mesh.edgesCount; edges++)
	// {
	// 	DrawEdge();
	// }
	texture = SDL_CreateTextureFromSurface(ctx->display->renderer, ctx->surface);
	SDL_RenderCopy(ctx->display->renderer, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}
