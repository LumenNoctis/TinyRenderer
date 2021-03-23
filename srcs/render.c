#include "Renderer.h"

void DrawScene(Scene *scene)
{
    int i;

    while(i < scene->nobjs)
    {
        DrawObject(scene->objects[i], scene);
        // exit(0);
        i++;
    }
}

void DrawObject(Object obj, Scene *scene)
{
    int i;

    i = 0;
    while (i  < obj.ntris)
    {
        if (scene->renderMode == 1)
        {
            DrawTriangle(obj.tris[i], scene);
        }
        else
            FillTriangle(obj.tris[i], scene);
        i++;
    }

    SDL_SetRenderDrawColor(scene->display->renderer, 0, 0, 0, 255);
}


void DrawTriangle(Triangle tri, Scene *scene)
{
    MT_Vector2 a;
    MT_Vector2 b;
    MT_Vector2 c;

    tri.vertices[0] = TransformPoint(tri.vertices[0], scene->cam);
    tri.vertices[1] = TransformPoint(tri.vertices[1], scene->cam);
    tri.vertices[2] = TransformPoint(tri.vertices[2], scene->cam);

    a = ToScreen(tri.vertices[0]);
    b = ToScreen(tri.vertices[1]);
    c = ToScreen(tri.vertices[2]);
    SDL_SetRenderDrawColor(scene->display->renderer,
                                    tri.color >> 24, tri.color >> 16, tri.color >>8,
                                    255);
    SDL_RenderDrawLine(scene->display->renderer,
                        a.x,
                        a.y,
                        b.x,
                        b.y);
    
    SDL_RenderDrawLine(scene->display->renderer,
                        b.x,
                        b.y,
                        c.x,
                        c.y);
    
    SDL_RenderDrawLine(scene->display->renderer,
                        c.x,
                        c.y,
                        a.x,
                        a.y);

}

void FillTriangle(Triangle tri, Scene *scene)
{
    MT_Vector2 start;
    MT_Vector2 end;
    MT_Vector2 vec;
    MT_Vector2 a;
    MT_Vector2 b;
    MT_Vector2 c;
    double i;
    double dist;
    double lighting;

    tri.vertices[0] = TransformPoint(tri.vertices[0], scene->cam);
    tri.vertices[1] = TransformPoint(tri.vertices[1], scene->cam);
    tri.vertices[2] = TransformPoint(tri.vertices[2], scene->cam);

    a = ToScreen(tri.vertices[0]);
    b = ToScreen(tri.vertices[1]);
    c = ToScreen(tri.vertices[2]);

    //Pretend vertices are sorted by Y for now
    end = b;
    start = a;

    i = 0;
    // printf("Lightng %f\n", lighting);
    // lighting *= 0xFF;
    // printf("Lightng C %f color %d \n", (int)lighting >> 24, color);
    SDL_SetRenderDrawColor(scene->display->renderer,
                         tri.color >> 24,
                         tri.color >> 16,
                         tri.color >>8,
                        255);
    dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)) * 1.5;
    vec = (MT_Vector2){(c.x - b.x) / dist, (c.y - b.y) / dist};
    while (i <= dist)
    {
        SDL_RenderDrawLine(scene->display->renderer,
                start.x,
                start.y,
                end.x,
                end.y);

        end.x += vec.x;
        end.y += vec.y;
        i++;
    }
}