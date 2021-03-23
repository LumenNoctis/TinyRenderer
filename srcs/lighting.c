#include "Renderer.h"

MT_Vector3 CalcNormals(Triangle tri)
{
    MT_Vector3 u;
    MT_Vector3 v;
    MT_Vector3 edgeA;
    MT_Vector3 edgeB;
    MT_Vector3 edgeC;
    MT_Vector3 result;

    edgeA = (MT_Vector3){tri.vertices[0].x - tri.vertices[1].x,
                         tri.vertices[0].y - tri.vertices[1].y,
                         tri.vertices[0].z - tri.vertices[1].z};
    edgeB = (MT_Vector3){tri.vertices[1].x - tri.vertices[2].x,
                         tri.vertices[1].y - tri.vertices[2].y,
                         tri.vertices[1].z - tri.vertices[2].z};
    edgeC = (MT_Vector3){tri.vertices[2].x - tri.vertices[0].x,
                         tri.vertices[2].y - tri.vertices[0].y,
                         tri.vertices[2].z - tri.vertices[0].z};
    
    u = MT_V3Sub(edgeB, edgeA);
    v = MT_V3Sub(edgeC, edgeA);

    result.x = (u.y * v.z) - (u.z * v.y);
    result.y = (u.z * v.x) - (u.x * v.z);
    result.z = (u.x * v.y) - (u.y * v.x);

    return result;
}

double CalcLighting(Triangle tri, MT_Vector3 LightDir)
{
    SDLX_Display *display;
    MT_Vector3 normal;
    MT_Vector3 c;
    MT_Vector2 s;
    MT_Vector2 e;
    
    display = SDLX_DisplayGet();

    normal = CalcNormals(tri);
    // normal = MT_V3Normalize(normal);

    s = ToScreen(tri.vertices[0]);
    e = ToScreen(MT_V3Add(tri.vertices[0], normal));

 SDL_SetRenderDrawColor(display->renderer,
                        0,
                        0,
                        200,
                        255);
    SDL_RenderDrawLine(display->renderer,
                s.x,
                s.y,
                e.x,
                e.y);


    return MAX(MT_V3Dot(normal, LightDir, NULL), 0.2);
}