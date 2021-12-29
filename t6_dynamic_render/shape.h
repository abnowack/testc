#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "math2d.h"

typedef struct
{
    vec3 pos;
    vec3 col;
} Vertex;

typedef struct
{
    Vertex *vertices;
    unsigned int n_vertices;
    unsigned int *indices;
    unsigned int n_indices;

    float angle;
    vec2 position;
} Shape;

Shape empty_Shape()
{
    Shape t = {.vertices = NULL, .n_vertices = 0, .indices = NULL, .n_indices = 0, .angle = 0, .position = {0, 0}};
    return t;
}

Shape random_Triangle(float size)
{
    Shape t = empty_Shape();

    t.n_vertices = 3;
    t.n_indices = 3;
    t.vertices = malloc(t.n_vertices * sizeof(Vertex));
    t.indices = malloc(t.n_indices * sizeof(unsigned int));

    float base = float_rand(0, size);
    float height = float_rand(0, size);

    t.vertices[0].pos.x = -base / 2;
    t.vertices[0].pos.y = -height / 2;
    t.vertices[1].pos.x = 0;
    t.vertices[1].pos.y = height / 2;
    t.vertices[2].pos.x = base / 2;
    t.vertices[2].pos.y = -height / 2;

    float r = float_rand(0, 1.0);
    float g = float_rand(0, 1.0);
    float b = float_rand(0, 1.0);
    for (unsigned int j = 0; j < t.n_vertices; j++)
    {
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

Shape random_Rectangle(float size)
{
    Shape t = empty_Shape();

    t.n_vertices = 4;
    t.n_indices = 6;
    t.vertices = malloc(t.n_vertices * sizeof(Vertex));
    t.indices = malloc(t.n_indices * sizeof(unsigned int));

    float r = float_rand(0, 1.0);
    float g = float_rand(0, 1.0);
    float b = float_rand(0, 1.0);

    float w = float_rand(-size, size);
    float h = float_rand(-size, size);

    float x1 = -w / 2;
    float x2 = w / 2;
    float y1 = h / 2;
    float y2 = -h / 2;

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

vec3 position_Shape(Shape *s, unsigned int n_vertex)
{
    float radian = M_PI * s->angle / 180.0f;
    vec3 pos;
    pos.x = s->vertices[n_vertex].pos.x * cosf(radian) - s->vertices[n_vertex].pos.y * sinf(radian) + s->position.x;
    pos.y = s->vertices[n_vertex].pos.x * sinf(radian) + s->vertices[n_vertex].pos.y * cosf(radian) + s->position.y;
    pos.z = 0;
    return pos;
}

void print_Shape(Shape *t)
{
    for (unsigned int j = 0; j < t->n_vertices; j++)
    {
        printf("X: %f  Y: %f  Z: %f\n", t->vertices[j].pos.x, t->vertices[j].pos.y, t->vertices[j].pos.z);
        printf("R: %f  G: %f  B: %f\n", t->vertices[j].col.r, t->vertices[j].col.g, t->vertices[j].col.b);
    }
}
