#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "includes.h"
#include "shader.h"
#include "vao.h"
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int WIDTH = 400;
const int HEIGHT = 400;
std::string TITLE = "learn opengl 2";

float vertices[] = {
    // position                                    // color            // texCoord
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

void processInputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw." << std::endl;
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (__APPLE__) {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    GLFWwindow *window;
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Shader shader("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");

    VAO vao;
    vao.setVertices(vertices, sizeof(vertices));
    vao.setIndices(indices, sizeof(indices));
    vao.enablePointer(0, 3, 8, 0);
    vao.enablePointer(1, 3, 8, 3);
    vao.enablePointer(2, 2, 8, 6);
    
    
    Texture containerTexture("./assets/container.jpeg", GL_RGB);
    Texture awesomefaceTexture("./assets/awesomeface.png", GL_RGBA);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInputs(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0));
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setUniformMatrix4fv("uMVP", model);

        containerTexture.use(shader, "uTexture1", GL_TEXTURE0, 0);
        awesomefaceTexture.use(shader, "uTexture2", GL_TEXTURE1, 1);
        vao.draw(shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(sin(glfwGetTime() * 10) / 2 + 0.5f, 1.0f, 0.0f));
        shader.setUniformMatrix4fv("uMVP", model);

        containerTexture.use(shader, "uTexture1", GL_TEXTURE0, 0);
        awesomefaceTexture.use(shader, "uTexture2", GL_TEXTURE1, 1);
        vao.draw(shader);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}