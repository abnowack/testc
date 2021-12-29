#include "glfw_utils.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "shape.h"
#include "render.h"
#include "math2d.h"

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

#define N_SHAPES 200

void update_positions(Shape *shapes, unsigned int n_shapes)
{
    return;
}

int main()
{
    srand((unsigned int)time(0));

    GLFWwindow *window = CreateWindow(800, 600, "My Window", 3, 3);

    unsigned int shaderProgram = createShader(vertexShaderSource, fragmentShaderSource);

    Render render;
    render_Setup(&render);

    Shape shapes[N_SHAPES];

    for (unsigned int i = 0; i < N_SHAPES; i++)
    {
        if (i % 2)
            shapes[i] = random_Triangle(0.3f);
        else
            shapes[i] = random_Rectangle(0.3f);
        
        shapes[i].position.x = float_rand(-1, 1);
        shapes[i].position.y = float_rand(-1, 1);
        shapes[i].angle = float_rand(0, 360);
    }

    double omega = 360;

     double lastTime = glfwGetTime();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        double currentTime = glfwGetTime();
        double dt = lastTime - currentTime;

        // physics
        for (unsigned int i = 0; i < N_SHAPES; i++)
        {
            shapes[i].angle += omega * dt;
            shapes[i].angle = fmod(shapes[i].angle, 360.0);
        } 


        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_CopyData(&render, shapes, N_SHAPES);

        glUseProgram(shaderProgram);
        render_Draw(&render);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = currentTime;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // glDeleteVertexArrays(2, VAOs);
    // glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
