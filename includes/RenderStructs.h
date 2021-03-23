#include "SDLX.h"
#include "MT.h"
#include "MT_vec3.h"

typedef struct Triangle
{
    MT_Vector3  vertices[3];
    int color;
}               Triangle;

typedef struct Line
{
    MT_Vector3 a;
    MT_Vector3 b;
}               Line;

typedef struct Vector4
{
    double x;
    double y;
    double z;
    double w;
}               Vector4;

typedef struct Object
{
    int     ntris;

    Triangle    *tris;
}               Object;

typedef struct Camera
{
    double scale;
    int     flen;
    MT_Vector3 position;
    MT_Vector3 rotation;
}               Camera;

typedef struct Scene
{
    int         nobjs;
    Camera      cam;
    Object      *objects;
    SDLX_Display *display;
    int     renderMode;
}              Scene;