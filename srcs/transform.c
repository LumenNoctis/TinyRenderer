#include "Renderer.h"
#include "MT_matrix.h"

static MT_Matrix mProject;
static double       _fov;
static double       _ratio;
static double       _fdist;
static double       _flen;

void        initTransforms()
{
    _fov = 1.0 / tan(MT_ToRadf(FOV / 2));
    _ratio = WIN_W / WIN_H;
    _fdist = 1;
    _flen = 300;

    mProject.m = 4; 
    mProject.n = 4;
    mProject.matrix[0][0] = _ratio * _fov; 
    mProject.matrix[0][1] = 0; 
    mProject.matrix[0][2] = 0; 
    mProject.matrix[0][3] = 0;
    
    mProject.matrix[1][0] = 0; 
    mProject.matrix[1][1] = _fov; 
    mProject.matrix[1][2] = 0; 
    mProject.matrix[1][3] = 0;
    
    mProject.matrix[2][0] = 0; 
    mProject.matrix[2][1] = 0; 
    mProject.matrix[2][2] = _flen / (_flen - _fdist); 
    mProject.matrix[2][3] = 1;
    
    mProject.matrix[3][0] = 0; 
    mProject.matrix[3][1] = 0; 
    mProject.matrix[3][2] = (-_flen * _fdist) / (_flen - _fdist);; 
    mProject.matrix[3][3] = 0;
}

MT_Matrix mult(MT_Matrix a, MT_Matrix b)
{
    MT_Matrix result;
    double     sum;

    result.m = a.n;
    result.n = b.m;

    // This is inverted, fix later
    result.matrix[0][0] = a.matrix[0][0] * b.matrix[0][0] +
                   a.matrix[1][0] * b.matrix[0][0] +
                   a.matrix[2][0] * b.matrix[0][0] +
                   a.matrix[3][0] * b.matrix[0][0];
    result.matrix[1][0] = a.matrix[0][0] * b.matrix[1][0] +
                   a.matrix[1][0] * b.matrix[1][1] +
                   a.matrix[2][0] * b.matrix[1][2] +
                   a.matrix[3][0] * b.matrix[1][3];
    result.matrix[2][0] = a.matrix[0][0] * b.matrix[2][0] +
                   a.matrix[1][0] * b.matrix[2][1] +
                   a.matrix[2][0] * b.matrix[2][2] +
                   a.matrix[3][0] * b.matrix[2][3];
    result.matrix[3][0] = a.matrix[0][0] * b.matrix[3][0] +
                   a.matrix[1][0] * b.matrix[3][1] +
                   a.matrix[2][0] * b.matrix[3][2] +
                   a.matrix[3][0] * b.matrix[3][3];

    result.matrix[0][1] = a.matrix[0][1] * b.matrix[0][0] +
                   a.matrix[1][1] * b.matrix[0][1] +
                   a.matrix[2][1] * b.matrix[0][2] +
                   a.matrix[3][1] * b.matrix[0][3];
    result.matrix[1][1] = a.matrix[0][1] * b.matrix[1][0] +
                   a.matrix[1][1] * b.matrix[1][1] +
                   a.matrix[2][1] * b.matrix[1][2] +
                   a.matrix[3][1] * b.matrix[1][3];
    result.matrix[2][1] = a.matrix[0][1] * b.matrix[2][0] +
                   a.matrix[1][1] * b.matrix[2][1] +
                   a.matrix[2][1] * b.matrix[2][2] +
                   a.matrix[3][1] * b.matrix[2][3];
    result.matrix[3][1] = a.matrix[0][1] * b.matrix[3][0] +
                   a.matrix[1][1] * b.matrix[3][1] +
                   a.matrix[2][1] * b.matrix[3][2] +
                   a.matrix[3][1] * b.matrix[3][3];

    result.matrix[0][2] = a.matrix[0][2] * b.matrix[0][0] +
                   a.matrix[1][2] * b.matrix[0][1] +
                   a.matrix[2][2] * b.matrix[0][2] +
                   a.matrix[3][2] * b.matrix[0][3];
    result.matrix[1][2] = a.matrix[0][2] * b.matrix[1][0] +
                   a.matrix[1][2] * b.matrix[1][1] +
                   a.matrix[2][2] * b.matrix[1][2] +
                   a.matrix[3][2] * b.matrix[1][3];
    result.matrix[2][2] = a.matrix[0][2] * b.matrix[2][0] +
                   a.matrix[1][2] * b.matrix[2][1] +
                   a.matrix[2][2] * b.matrix[2][2] +
                   a.matrix[3][2] * b.matrix[2][3];
    result.matrix[3][2] = a.matrix[0][2] * b.matrix[3][0] +
                   a.matrix[1][2] * b.matrix[3][1] +
                   a.matrix[2][2] * b.matrix[3][2] +
                   a.matrix[3][2] * b.matrix[3][3];

    result.matrix[0][3] = a.matrix[0][3] * b.matrix[0][0] +
                   a.matrix[1][3] * b.matrix[0][1] +
                   a.matrix[2][3] * b.matrix[0][2] +
                   a.matrix[3][3] * b.matrix[0][3];
    result.matrix[1][3] = a.matrix[0][3] * b.matrix[1][0] +
                   a.matrix[1][3] * b.matrix[1][1] +
                   a.matrix[2][3] * b.matrix[1][2] +
                   a.matrix[3][3] * b.matrix[1][3];
    result.matrix[2][3] = a.matrix[0][3] * b.matrix[2][0] +
                   a.matrix[1][3] * b.matrix[2][1] +
                   a.matrix[2][3] * b.matrix[2][2] +
                   a.matrix[3][3] * b.matrix[2][3];
    result.matrix[3][3] = a.matrix[0][3] * b.matrix[3][0] +
                   a.matrix[1][3] * b.matrix[3][1] +
                   a.matrix[2][3] * b.matrix[3][2] +
                   a.matrix[3][3] * b.matrix[3][3];
    return result;
}

MT_Vector2 ToScreen(MT_Vector3 point3D)
{
    MT_Matrix pointMatrix = {0};

    bzero(&pointMatrix, sizeof(pointMatrix));
    MT_Vector2 point2D;

    pointMatrix.m = 4;
    pointMatrix.n = 1;

    pointMatrix.matrix[0][0] = point3D.x; 
    pointMatrix.matrix[0][1] = point3D.y; 
    pointMatrix.matrix[0][2] = point3D.z; 
    pointMatrix.matrix[0][3] = 1;
    
    pointMatrix = mult(pointMatrix, mProject);
    if (pointMatrix.matrix[3][3] != 0)
    {
        pointMatrix.matrix[0][1] /= pointMatrix.matrix[3][3];
        pointMatrix.matrix[0][2] /= pointMatrix.matrix[3][3];
        pointMatrix.matrix[0][3] /= pointMatrix.matrix[3][3];
    }
    point3D.x = pointMatrix.matrix[0][2];
    point3D.y = pointMatrix.matrix[0][1];
    point3D.z = pointMatrix.matrix[0][0];
    point2D.x = (point3D.x + 1 ) * (WIN_H * 0.5);
    point2D.y = (point3D.y + 1 ) * (WIN_H * 0.5);

    return point2D;
}

void printmat(MT_Matrix mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%f ", mat.matrix[i][j]);
        printf("\n"); 
    }
        printf("-----------\n"); 
}

MT_Vector3 RotatePoint(MT_Vector3 point, MT_Vector3 rotation)
{
    MT_Matrix pointMatrix = {0};
    MT_Matrix zrotMatrix = {0};
    MT_Matrix xrotMatrix = {0};

    pointMatrix.m = 4;
    pointMatrix.n = 1;

    pointMatrix.matrix[0][0] = point.x; 
    pointMatrix.matrix[0][1] = point.y; 
    pointMatrix.matrix[0][2] = point.z; 
    pointMatrix.matrix[0][3] = 1;
    
    // rotMatrix.m = 4; 
    // rotMatrix.n = 4;
    
    zrotMatrix.matrix[0][0] = 1; 
    zrotMatrix.matrix[1][1] = cosf(MT_ToRadf(-rotation.y)); 
    zrotMatrix.matrix[1][2] = -sinf(MT_ToRadf(-rotation.y)); 
    zrotMatrix.matrix[2][1] = sinf(MT_ToRadf(-rotation.y)); 
    zrotMatrix.matrix[2][2] = cosf(MT_ToRadf(-rotation.y)); 
    zrotMatrix.matrix[3][3] = 1; 
    
    // rotMatrix.matrix[0][0] = cosf(MT_ToRadf(-rotation.x)); 
    // rotMatrix.matrix[0][2] = sinf(MT_ToRadf(-rotation.x)); 
    // rotMatrix.matrix[1][1] = 1; 
    // rotMatrix.matrix[2][0] = sinf(MT_ToRadf(-rotation.x)); 
    // rotMatrix.matrix[2][3] = cosf(MT_ToRadf(-rotation.x)); 
    // rotMatrix.matrix[3][3] = 1; 
    
    xrotMatrix.matrix[0][0] = cosf(MT_ToRadf(-rotation.x)); 
    xrotMatrix.matrix[0][1] = sinf(MT_ToRadf(-rotation.x)); 
    xrotMatrix.matrix[1][0] = sinf(MT_ToRadf(-rotation.x)); 
    xrotMatrix.matrix[1][1] = cosf(MT_ToRadf(-rotation.x)); 
    xrotMatrix.matrix[2][2] = 1; 
    // rotMatrix.matrix[2][2] = cosf(MT_ToRadf(-rotation.x)); 

    pointMatrix = mult(mult(xrotMatrix, zrotMatrix), pointMatrix);
    point.x = pointMatrix.matrix[0][0];
    point.y = pointMatrix.matrix[0][1];
    point.z = pointMatrix.matrix[0][2];

    return point;
}

MT_Vector3 TranslatePoint(MT_Vector3 point, MT_Vector3 translation)
{
    return MT_V3Add(point, translation);
}

MT_Vector3 ScalePoint(MT_Vector3 point, double scale)
{
    return MT_V3Scale(point, scale);
}

MT_Vector3 TransformPoint(MT_Vector3 point, Camera cam)
{
    point = RotatePoint(point, cam.rotation);
    point = TranslatePoint(point, cam.position);
    point = ScalePoint(point, cam.scale);

    return point;
}