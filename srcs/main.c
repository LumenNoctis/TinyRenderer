#include "Renderer.h"

int main()
{
    Scene *scene;

    initScene();
    initTransforms();
    scene = GetScene();
    while (1)
    {
        PollInput(scene);
        DrawScene(scene);
        SDL_RenderPresent(scene->display->renderer);
        SDLX_ResetWindow();
    }
}