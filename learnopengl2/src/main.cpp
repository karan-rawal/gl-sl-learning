#include "includes.h"
#include "shader/shader.h"
#include "window/window.h"
#include "utils/disposable.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define __APPLE true

const int WIDTH = 800;
const int HEIGHT = 800;

    float vertices[] = {
        // positions          // colors           // texture coords
         -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
          0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
          0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
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

unsigned int createEBO()
{
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    return ebo;
}

Shader shader;
unsigned int vao;
unsigned int vbo;
unsigned int ebo;
unsigned int texture;


void onUpdate(Window *window)
{
    processInputs(window->window);

    glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.uniform1f("colorMultiplier", sin(glfwGetTime() * 0.2f) / 2.f + 0.5f);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window->window);
    glfwPollEvents();
}

int main()
{
    Window window(WIDTH, HEIGHT, "learnopengl2");

    shader = Shader("./src/vertex_shader.glsl", "./src/fragment_shader.glsl");

    vao = createVAO();
    vbo = createVBO();
    ebo = createEBO();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, channels;
    unsigned char *data = stbi_load("assets/container.jpeg", &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load image file." << std::endl;
        shader.dispose();
        window.dispose();
    }
    stbi_image_free(data);

    window.show(onUpdate);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    shader.dispose();
    window.dispose();
    return 0;
}