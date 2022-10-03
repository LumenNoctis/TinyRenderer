#include "renderer.h"

void DrawVertices(MeshRender_t *render, Mesh_t mesh, int trace, SDLX_Display *display)
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
			// uint32_t *pixelUint = (uint32_t *)render->pixels;
			uint32_t *traceUint = (uint32_t *)render->trace;

			// pixelUint[display->win_w * screenCoord.y + screenCoord.x] = 0xFF0000FF;
			// if(trace)
				traceUint[display->win_w * screenCoord.y + screenCoord.x] = 0xFF0000FF;

			// z_buffer[screenCoord.x * screenCoord.y] = mesh.vertices[i].coordinates.z;
		}
	}
}

void DrawEdges(MeshRender_t *render, Mesh_t mesh, int trace, SDLX_Display *display)
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
	SDL_Texture	*pixeltexture;
	SDL_Texture	*tracetexture;


	// memset(ctx->render.pixels, 0x000000, ctx->display->win_h * ctx->display->win_w * PIXEL_CHANNELS * 2);

	if (ctx->settings.trace)
	{
		DrawVertices(&(ctx->render), ctx->mesh, ctx->settings.trace, ctx->display);
	}
	DrawEdges	(&(ctx->render), ctx->mesh, ctx->settings.trace, ctx->display);

	pixeltexture = SDL_CreateTextureFromSurface(ctx->display->renderer, ctx->render.pixelSurf);
	tracetexture = SDL_CreateTextureFromSurface(ctx->display->renderer, ctx->render.traceSurf);
	SDL_RenderCopy(ctx->display->renderer, pixeltexture, NULL, NULL);
	SDL_RenderCopy(ctx->display->renderer, tracetexture, NULL, NULL);
	SDL_DestroyTexture(pixeltexture);
	SDL_DestroyTexture(tracetexture);
}
