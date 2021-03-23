#include "Renderer.h"

void PollInput(Scene *scene)
{
    SDL_Event event;
    SDLX_Input input;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_Z)
                scene->renderMode ^= 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_A)
                scene->cam.rotation.y -= 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_D)
                scene->cam.rotation.y += 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_W)
                scene->cam.rotation.x += 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_S)
                scene->cam.rotation.x -= 1;
           
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                scene->cam.position.y -= 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                scene->cam.position.y += 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                scene->cam.position.x += 1;
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                scene->cam.position.x -= 1;
        }
        if (event.type == SDL_MOUSEWHEEL)
            scene->cam.scale += event.wheel.y;
        if (scene->cam.scale < 1)
            scene->cam.scale = 1;
    }

    // SDLX_InputUpdate(event);
    // input = SDLX_InputGet();

    // scene->cam.position.x += input.input[SDLX_RIGHT];
    // scene->cam.position.x -= input.input[SDLX_LEFT];
    // scene->cam.position.y += input.input[SDLX_UP];
    // scene->cam.position.y -= input.input[SDLX_DOWN];
}