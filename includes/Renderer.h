#ifndef RENDERER_H
# define RENDERER_H

# include "RenderStructs.h"

# define FOV (90.0)

void initScene(void);
Scene *GetScene(void);

void PollInput(Scene *scene);


// Make the arguments consistent in their positon
void DrawScene(Scene *scene);
void DrawObject(Object obj, Scene *scene);
void DrawTriangle( Triangle face, Scene *scene);
void DrawLine(MT_Vector3 start, MT_Vector3 end, Scene *scene);
void FillTriangle(Triangle tri, Scene *scene);

void printmat(MT_Matrix mat);

double CalcLighting(Triangle tri, MT_Vector3 LightDir);

void initTransforms();
MT_Vector2 ToScreen(MT_Vector3 point3D);
MT_Vector3 TransformPoint(MT_Vector3 point, Camera cam);

#endif