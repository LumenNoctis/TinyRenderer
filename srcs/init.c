#include "Renderer.h"

static struct Scene scene;

Object makeCube(MT_Vector3 origin, MT_Vector3 dimensions, int color)
{
    Object cube;
    MT_Vector3 verts[8];

    cube.ntris = 12;

    cube.tris = calloc(cube.ntris, sizeof(Triangle));

    verts[0].x = origin.x + (dimensions.x / 2);
    verts[0].y = origin.y + (dimensions.y / 2);
    verts[0].z = origin.z + (dimensions.z / 2);

    verts[1].x = origin.x + (dimensions.x / 2);
    verts[1].y = origin.y - (dimensions.y / 2);
    verts[1].z = origin.z + (dimensions.z / 2);

    verts[2].x = origin.x - (dimensions.x / 2);
    verts[2].y = origin.y - (dimensions.y / 2);
    verts[2].z = origin.z + (dimensions.z / 2);

    verts[3].x = origin.x - (dimensions.x / 2);
    verts[3].y = origin.y + (dimensions.y / 2);
    verts[3].z = origin.z + (dimensions.z / 2);

    verts[4].x = origin.x - (dimensions.x / 2);
    verts[4].y = origin.y + (dimensions.y / 2);
    verts[4].z = origin.z - (dimensions.z / 2);

    verts[5].x = origin.x + (dimensions.x / 2);
    verts[5].y = origin.y + (dimensions.y / 2);
    verts[5].z = origin.z - (dimensions.z / 2);
    
    verts[6].x = origin.x + (dimensions.x / 2);
    verts[6].y = origin.y - (dimensions.y / 2);
    verts[6].z = origin.z - (dimensions.z / 2);

    verts[7].x = origin.x - (dimensions.x / 2);
    verts[7].y = origin.y - (dimensions.y / 2);
    verts[7].z = origin.z - (dimensions.z / 2);

    cube.tris[0].vertices[0] = verts[4];
    cube.tris[0].vertices[1] = verts[5];
    cube.tris[0].vertices[2] = verts[0];
    cube.tris[0].color = 0xFF000000;

    cube.tris[1].vertices[0] = verts[4];
    cube.tris[1].vertices[1] = verts[3];
    cube.tris[1].vertices[2] = verts[0];
    cube.tris[1].color = 0xFF000000;

    cube.tris[2].vertices[0] = verts[2];
    cube.tris[2].vertices[1] = verts[7];
    cube.tris[2].vertices[2] = verts[1];
    cube.tris[2].color = 0xFF000000;

    cube.tris[3].vertices[0] = verts[7];
    cube.tris[3].vertices[1] = verts[6];
    cube.tris[3].vertices[2] = verts[1];
    cube.tris[3].color = 0xFF000000;

    cube.tris[4].vertices[0] = verts[5];
    cube.tris[4].vertices[1] = verts[4];
    cube.tris[4].vertices[2] = verts[7];
    cube.tris[4].color = 0x00FF0000;

    cube.tris[5].vertices[0] = verts[5];
    cube.tris[5].vertices[1] = verts[6];
    cube.tris[5].vertices[2] = verts[7];
    cube.tris[5].color = 0x00FF0000;

    cube.tris[6].vertices[0] = verts[0];
    cube.tris[6].vertices[1] = verts[3];
    cube.tris[6].vertices[2] = verts[2];
    cube.tris[6].color = 0x00FF0000;

    cube.tris[7].vertices[0] = verts[2];
    cube.tris[7].vertices[1] = verts[0];
    cube.tris[7].vertices[2] = verts[1];
    cube.tris[7].color = 0x00FF0000;

    cube.tris[8].vertices[0] = verts[0];
    cube.tris[8].vertices[1] = verts[6];
    cube.tris[8].vertices[2] = verts[1];
    cube.tris[8].color = 0x0000FF00;

    cube.tris[9].vertices[0] = verts[0];
    cube.tris[9].vertices[1] = verts[5];
    cube.tris[9].vertices[2] = verts[6];
    cube.tris[9].color = 0x0000FF00;

    cube.tris[10].vertices[0] = verts[3];
    cube.tris[10].vertices[1] = verts[4];
    cube.tris[10].vertices[2] = verts[7];
    cube.tris[10].color = 0x0000FF00;

    cube.tris[11].vertices[0] = verts[3];
    cube.tris[11].vertices[1] = verts[2];
    cube.tris[11].vertices[2] = verts[7];
    cube.tris[11].color = 0x0000FF00;

    return cube;

}

void initScene(void)
{
    Object test;
        
    SDLX_Start("Renderer", WIN_X, WIN_Y, WIN_H, WIN_W, 0);

    scene.display = SDLX_DisplayGet();

    scene.renderMode = 0;
    scene.cam.scale = 1;

    scene.cam.position.x = 0;
    scene.cam.position.y = 0;
    scene.cam.position.z = 0;

    scene.cam.rotation.x = 0;
    scene.cam.rotation.y = 0;

    scene.nobjs = 1;
    scene.objects = calloc(scene.nobjs, sizeof(Object));

    // test.ntris = 1;
    // test.nverts = 0;
    // test.nlines = 0;
    // test.tris = calloc(test.ntris, sizeof(Triangle));

    // test.tris[0].vertices[0].x = 0;
    // test.tris[0].vertices[0].y = 0;
    // test.tris[0].vertices[0].z = 10;
    
    // test.tris[0].vertices[1].x = 0;
    // test.tris[0].vertices[1].y = 100;
    // test.tris[0].vertices[1].z = 10;

    // test.tris[0].vertices[2].x = 100;
    // test.tris[0].vertices[2].y = 0;
    // test.tris[0].vertices[2].z = 10;

    SDLX_InputMap(SDL_SCANCODE_LEFT, 1, SDLX_LEFT, -1);
    SDLX_InputMap(SDL_SCANCODE_RIGHT, 1, SDLX_RIGHT, -1);
    SDLX_InputMap(SDL_SCANCODE_UP, 1, SDLX_UP, -1);
    SDLX_InputMap(SDL_SCANCODE_DOWN, 1, SDLX_DOWN, -1);

    // test.color = 0xFF000000;
    scene.objects[0] = makeCube((MT_Vector3){0,0,0}, (MT_Vector3){1,1,1}, 0xFF000000);
}

Scene *GetScene(void) { return &scene; }