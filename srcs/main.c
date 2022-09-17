/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:53:55 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/18 22:53:22 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	main(int argc, char **argv)
{
	RenderContext_t *ctx;

	ctx = initRenderContext();
	while (1)
	{
		SDLX_RenderReset(ctx->display);
		SDLX_InputUpdate();
		SDLX_InputLoop();
		DrawMesh(ctx);
		SDL_RenderPresent(ctx->display->renderer);
	}
	// char	**map;
	// int		len;
	// len = 0;
	// if (argc != 2)
	// 	exit(write_error(2));
	// map = error_loop(argv[1], &len);
	// parse_file(map, len);
	exit(0);
}
