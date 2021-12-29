#include "glfw_utils.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shape.h"

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

void construct_Shape(struct Shape *t)
{
    glGenVertexArrays(1, &t->VAO);
    glGenBuffers(1, &t->VBO);
    glBindVertexArray(t->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, t->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * t->n_vertices, t->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void draw_Shape(struct Shape *t)
{
    glBindVertexArray(t->VAO);
    glDrawArrays(GL_TRIANGLES, 0, t->n_vertices);
}

#define N_SHAPES 100

int main()
{
    srand(time(0));

    GLFWwindow *window = CreateWindow(800, 600, "My Window", 3, 3);

    unsigned int shaderProgram = createShader(vertexShaderSource, fragmentShaderSource);

    struct Shape triangles[N_SHAPES];

    for (unsigned int i = 0; i < N_SHAPES; i++)
    {
        // triangles[i] = random_Triangle();
        triangles[i] = random_Rectangle(0.3);
        construct_Shape(&triangles[i]);
    }

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        for (unsigned int i = 0; i < N_SHAPES; i++)
        {
            draw_Shape(&triangles[i]);
        }

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
