#include "glfw_utils.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "shape.h"
#include "render.h"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 position;\n"
                                 "layout (location = 1) in vec3 color;\n"
                                 "out vec3 Color;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   Color = color;"
                                 "   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 Color;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(Color, 1.0f);\n"
                                   "}\n\0";

#define N_SHAPES 20

void update_positions(struct Shape *shapes, unsigned int n_shapes)
{
    return;
}

int main()
{
    srand((unsigned int)time(0));

    GLFWwindow *window = CreateWindow(800, 600, "My Window", 3, 3);

    unsigned int shaderProgram = createShader(vertexShaderSource, fragmentShaderSource);

    struct Render render;
    render_Setup(&render);

    struct Shape shapes[N_SHAPES];

    for (unsigned int i = 0; i < N_SHAPES; i++)
    {
        if (i % 2)
            shapes[i] = random_Triangle();
        else
            shapes[i] = random_Rectangle(0.3f);
    }

    // copy vertices to batch
    // move this in render step
    // unsigned int nvertex_count = 0;
    // render.n_vertex = 0;
    // render.n_index = 0;
    // for (unsigned int i = 0; i < N_SHAPES; i++)
    // {
    //     for (unsigned int j = 0; j < shapes[i].n_vertices; j++)
    //     {
    //         render.vertex_data[render.n_vertex] = shapes[i].vertices[j];
    //         render.n_vertex++;
    //     }
    //     nvertex_count += shapes[i].n_vertices;
    //     render.n_index += 6;
    // }

    // for(unsigned int i = 0; i < render.n_vertex; i++)
    // {
    //     fprintf(stderr, "%d | x: %.3f y %.3f z %.3f\n", i, render.vertex_data[i].pos.x, render.vertex_data[i].pos.y, render.vertex_data[i].pos.z);
    // }

    // for(unsigned int i = 0; i < render.n_index; i++)
    // {
    //     fprintf(stderr, "%d ", render.index_data[i]);
    // }
    // fprintf(stderr, "\n");


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // physics
        update_positions(shapes, N_SHAPES);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_CopyData(&render, shapes, N_SHAPES);

        glUseProgram(shaderProgram);
        render_Draw(&render);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // glDeleteVertexArrays(2, VAOs);
    // glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
