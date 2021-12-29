#include <stdio.h>
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

struct Vertex
{
    vec3 pos;
    vec3 col;
};

struct Shape
{
    struct Vertex *vertices;
    unsigned int n_vertices;
    unsigned int *indices;
    unsigned int n_indices;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

float float_rand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);       /* [min, max] */
}

struct Shape random_Triangle()
{
    struct Shape t;

    t.n_vertices = 3;
    t.n_indices = 3;
    t.vertices = malloc(t.n_vertices * sizeof(struct Vertex));
    t.indices = malloc(t.n_indices * sizeof(unsigned int));

    float r = float_rand(0, 1.0);
    float g = float_rand(0, 1.0);
    float b = float_rand(0, 1.0);
    for (unsigned int j = 0; j < t.n_vertices; j++)
    {
        t.vertices[j].pos.x = float_rand(-1, 1.0);
        t.vertices[j].pos.y = float_rand(-1, 1.0);
        t.vertices[j].pos.z = 0;
        t.vertices[j].col.r = r;
        t.vertices[j].col.g = g;
        t.vertices[j].col.b = b;
    }
    for (unsigned int j = 0; j < t.n_indices; j++)
    {
        t.indices[j] = j;
    }

    return t;
}

struct Shape random_Rectangle(float size)
{
    struct Shape t;

    t.n_vertices = 4;
    t.n_indices = 6;
    t.vertices = malloc(t.n_vertices * sizeof(struct Vertex));
    t.indices = malloc(t.n_indices * sizeof(unsigned int));

    float r = float_rand(0, 1.0);
    float g = float_rand(0, 1.0);
    float b = float_rand(0, 1.0);

    float x1 = float_rand(-1, 1);
    float y1 = float_rand(-1, 1);
    float x2 = float_rand(x1, x1 + size);
    float y2 = float_rand(y1, y1 + size);

    t.vertices[0].pos.x = x1;
    t.vertices[0].pos.y = y1;
    t.vertices[0].pos.z = 0;

    t.vertices[1].pos.x = x1;
    t.vertices[1].pos.y = y2;
    t.vertices[1].pos.z = 0;

    t.vertices[2].pos.x = x2;
    t.vertices[2].pos.y = y1;
    t.vertices[2].pos.z = 0;

    t.vertices[3].pos.x = x2;
    t.vertices[3].pos.y = y2;
    t.vertices[3].pos.z = 0;

    t.indices[0] = 0;
    t.indices[1] = 1;
    t.indices[2] = 2;
    t.indices[3] = 3;
    t.indices[4] = 1;    
    t.indices[5] = 2;    

    for (unsigned int j = 0; j < t.n_vertices; j++)
    {
        t.vertices[j].col.r = r;
        t.vertices[j].col.g = g;
        t.vertices[j].col.b = b;
    }
    return t;
}

void print_Shape(struct Shape *t)
{
    printf("VAO: %d    VBO: %d\n", t->VAO, t->VBO);
    for (unsigned int j = 0; j < t->n_vertices; j++)
    {
        printf("X: %f  Y: %f  Z: %f\n", t->vertices[j].pos.x, t->vertices[j].pos.y, t->vertices[j].pos.z);
        printf("R: %f  G: %f  B: %f\n", t->vertices[j].col.r, t->vertices[j].col.g, t->vertices[j].col.b);
    }
}