#include "includes.h"
#include "shader/shader.h"
#include "window/window.h"
#include "utils/disposable.h"

#define __APPLE true

const int WIDTH = 800;
const int HEIGHT = 800;

float vertices[] = {
    // position         color
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // top center
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // bottom right
};

void processInputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int createVAO()
{
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

unsigned int createVBO()
{
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    return vbo;
}

Shader shader;
unsigned int vao;
unsigned int vbo;

void onUpdate(Window *window)
{
    glfwPollEvents();
    processInputs(window->window);

    glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    shader.uniform1f("colorMultiplier", sin(glfwGetTime()) / 2.f + 0.5f);
    shader.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window->window);
}

int main()
{
    Window window(WIDTH, HEIGHT, "learnopengl2");

    shader = Shader("./src/vertex_shader.glsl", "./src/fragment_shader.glsl");

    vao = createVAO();
    vbo = createVBO();


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    window.show(onUpdate);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    shader.dispose();
    window.dispose();
    return 0;
}