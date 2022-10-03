/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:40:34 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 03:38:44 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void HandleInput(RenderContext_t *ctx)
{
	SDLX_Input input;

	input = SDLX_InputGet();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		// SDL_Log("Wheel %d", event.wheel.type);
		// SDL_Log("MOTIOn %d", event.motion);
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			exit(0);
		if(event.type == SDL_MOUSEWHEEL)
		{
			ctx->mesh.scale += (event.wheel.y  * 5);
		}
	}
	// ctx->mesh.rotation.y = 80;
	// (input.mouse_buttons[SDL_BUTTON_MIDDLE]);
	ctx->mesh.rotation.y -= (input.keyboard[KEY_LEFT] & 1) * 0.05;
	ctx->mesh.rotation.y += (input.keyboard[KEY_RIGHT] & 1) * 0.05;
	ctx->mesh.rotation.x += (input.keyboard[KEY_UP] & 1) * 0.05;
	ctx->mesh.rotation.x -= (input.keyboard[KEY_DOWN] & 1) * 0.05;

	ctx->mesh.scale += (input.keyboard[KEY_ZOOMU] & 1) * 0.01;
	ctx->mesh.scale -= (input.keyboard[KEY_ZOOMD] & 1) * 0.01;


	if (input.keyboard[KEY_SHIFT])
	{
		if (SDLX_GetKeyState(KEY_TRACE) == SDLX_KEYDOWN)
		{
			memset(ctx->render.trace, 0x000000, ctx->display->win_h * ctx->display->win_w * PIXEL_CHANNELS * 2);
		}

	}
	else {
		if (SDLX_GetKeyState(KEY_TRACE) == SDLX_KEYUP)
		{
			ctx->settings.trace ^= 1;
		}
	}

	if (input.keyboard[KEY_RESET])
	{
		ctx->mesh.rotation.y = 0;
		ctx->mesh.rotation.x = 0;
	}
}
