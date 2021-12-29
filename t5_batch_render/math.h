#include <stdlib.h>

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

float float_rand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);       /* [min, max] */
}