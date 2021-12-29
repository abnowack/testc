#pragma once

#include <stdlib.h>
#include <math.h>

#define M_PI 3.1415926536897f

typedef struct
{
    union
    {
        struct
        {
            float x;
            float y;
        };
        float xy[2];
    };

} vec2;

typedef struct
{
    union
    {
        union
        {
            struct
            {
                float x;
                float y;
                float z;
            };
            float xyz[3];
        };
        union
        {
            struct
            {
                float r;
                float g;
                float b;
            };
            float rgb[3];
        };
    };
} vec3;

typedef struct
{
    union
    {
        struct
        {
            float a1;
            float a2;
            float b1;
            float b2;
        };
        float data[4];
        float d[2][2];
    };
} mat2x2;

float float_rand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);       /* [min, max] */
}

// mat2x2 identity_matrix()
// {
//     mat2x2 m;
//     m.d[0][0] = 1;
//     m.d[0][1] = 0;
//     m.d[1][0] = 0;
//     m.d[1][1] = 1;
//     return m;
// }

// mat2x2 rotation_matrix(float angle)
// {
//     mat2x2 m; //= {1, 0, 0, 1};

//     float radian = 2 * M_PI * angle / 180.0f;
//     m.d[0][0] = cosf(radian);
//     m.d[0][1] = sinf(radian);
//     m.d[1][0] = -sinf(radian);
//     m.d[1][1] = cosf(radian);
//     return m;
// }

// vec3 apply_Transform(vec3 pos, mat2x2 transform)
// {
//     vec3 out;
//     out.x = pos.x * transform.a1 + pos.y * transform.a2;
//     out.y = pos.x * transform.b1 + pos.y * transform.b2;
//     out.z = pos.z;
//     return out;
// }