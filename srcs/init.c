#include "renderer.h"

void initControls(void)
{
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LEFT, KEY_LEFT);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_A, 	KEY_LEFT);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_RIGHT,KEY_RIGHT);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_D, 	KEY_RIGHT);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_UP, 	KEY_UP);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_W, 	KEY_UP);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_DOWN, KEY_DOWN);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_S, 	KEY_DOWN);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_Q, 	KEY_ZOOMU);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_E, 	KEY_ZOOMD);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_R, 	KEY_RESET);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_TAB, 	KEY_MODE);

	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_T, 	KEY_TRACE);


	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_LSHIFT, KEY_SHIFT);
	SDLX_InputMap(SDLX_KEYBOARDTYPE, SDL_SCANCODE_RSHIFT, KEY_SHIFT);
}

void initSurfaces(MeshRender_t *render)
{
	render->pixels = calloc(DEFAULT_WIN_H * DEFAULT_WIN_W * 3, sizeof(uint32_t));
	render->trace = render->pixels +   (DEFAULT_WIN_H * DEFAULT_WIN_W * sizeof(uint32_t));
	render->z_buffer = render->trace + (DEFAULT_WIN_H * DEFAULT_WIN_W * sizeof(uint32_t));

	render->pixelSurf = SDL_CreateRGBSurfaceFrom(
		render->pixels,
		DEFAULT_WIN_W,
		DEFAULT_WIN_H,
		PIXEL_CHANNELS * 8,
		DEFAULT_WIN_W * PIXEL_CHANNELS,
		*((Uint32 *)(&(SDL_Color){.r = 255, .g = 000, .b = 000, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 255, .b = 000, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 000, .b = 255, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 000, .b = 000, .a = 255}))
		);

	render->traceSurf = SDL_CreateRGBSurfaceFrom(
		render->trace,
		DEFAULT_WIN_W,
		DEFAULT_WIN_H,
		PIXEL_CHANNELS * 8,
		DEFAULT_WIN_W * PIXEL_CHANNELS,
		*((Uint32 *)(&(SDL_Color){.r = 255, .g = 000, .b = 000, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 255, .b = 000, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 000, .b = 255, .a = 000})),
		*((Uint32 *)(&(SDL_Color){.r = 000, .g = 000, .b = 000, .a = 255}))
		);
}

void initSettings(Settings_t *settings)
{
	settings->mode = MODE_VIEW;
	settings->trace = 1;
}

RenderContext_t *initRenderContext(void)
{
	RenderContext_t *ctx;

	SDLX_InitDefault();

	ctx = SDL_calloc(1, sizeof(*ctx));
	ctx->display = SDLX_DisplayGet();

	initControls();
	initSurfaces(&ctx->render);
	initSettings(&ctx->settings);

	LoadObjFile(&ctx->mesh, "assets/wireframe.obj");

	return ctx;
}
