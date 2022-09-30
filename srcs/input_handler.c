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

	// ctx->mesh.rotation.y = 80;
	// (input.mouse_buttons[SDL_BUTTON_MIDDLE]);
	ctx->mesh.rotation.y -= (input.keyboard[KEY_LEFT] & 1) * 0.05;
	ctx->mesh.rotation.y += (input.keyboard[KEY_RIGHT] & 1) * 0.05;
	ctx->mesh.rotation.x += (input.keyboard[KEY_UP] & 1) * 0.05;
	ctx->mesh.rotation.x -= (input.keyboard[KEY_DOWN] & 1) * 0.05;


	ctx->mesh.scale -= (input.keyboard[KEY_DR] & 1) * 0.01;
	ctx->mesh.scale += (input.keyboard[KEY_DL] & 1) * 0.01;

	SDL_Log("Rot: %f %f", ctx->mesh.rotation.x, ctx->mesh.rotation.y );
	if (input.keyboard[KEY_ZOOM])
	{
		ctx->mesh.rotation.y = 0;
		ctx->mesh.rotation.x = 0;
	}
}
