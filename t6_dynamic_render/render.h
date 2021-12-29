#pragma once
#include <GLFW/glfw3.h>

struct Vertex;

#define MAX_QUADS 1000
#define MAX_VERTEX_COUNT (MAX_QUADS * 4)
#define MAX_INDEX_COUNT (MAX_QUADS * 6)

typedef struct
{
    Vertex vertex_data[MAX_VERTEX_COUNT];
    unsigned int n_vertex;
    unsigned int index_data[MAX_INDEX_COUNT];
    unsigned int n_index;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
} Render;

void render_Setup(Render *r)
{
    glGenVertexArrays(1, &r->VAO);
    glGenBuffers(1, &r->VBO);
    glGenBuffers(1, &r->EBO);
    glBindVertexArray(r->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_COUNT * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDEX_COUNT * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);    
}

void render_CopyData(Render *r, Shape shapes[], unsigned int n_shapes)
{
    r->n_vertex = 0;
    r->n_index = 0;

    for (unsigned int i = 0; i < n_shapes; i++)
    {
        // copy vertex data
        unsigned int first_vertex = r->n_vertex;
        for (unsigned int j = 0; j < shapes[i].n_vertices; j++)
        {
            r->vertex_data[r->n_vertex].pos = position_Shape(&shapes[i], j);
            r->vertex_data[r->n_vertex].col = shapes[i].vertices[j].col;
            r->n_vertex++;
        }

        // copy index data
        unsigned int first_index = r->n_index;
        for (unsigned int j = 0; j < shapes[i].n_indices; j++)
        {
            r->index_data[r->n_index] = shapes[i].indices[j] + first_vertex;
            r->n_index++;
        }
    }
}

void render_Draw(Render *r)
{
    glBindBuffer(GL_ARRAY_BUFFER, r->EBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(r->index_data), r->index_data);

    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(r->vertex_data), r->vertex_data);

    glBindVertexArray(r->VAO);
    glDrawElements(GL_TRIANGLES, r->n_index, GL_UNSIGNED_INT, 0);
}