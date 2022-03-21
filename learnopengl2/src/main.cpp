#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <math.h>

#define __APPLE true

const int WIDTH = 800;
const int HEIGHT = 800;

float vertices[] = {
    // position         color
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
     0.0f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // top center
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // bottom right
};

void processInputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int createVAO() {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

unsigned int createVBO() {
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    return vbo;
}

unsigned int createShader(char const *shaderPath, unsigned int shaderType) {
    std::ifstream inputFile(shaderPath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string shaderSource = buffer.str();
    char const *shaderCode = shaderSource.c_str();
    
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        int infoLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        char errorMessage[infoLength];
        glGetShaderInfoLog(shader, infoLength, NULL, errorMessage);
        std::cout << "Failed to compile shader " << shaderPath << ": " << errorMessage << std::endl;
        return -1;
    }

    return shader;
}

unsigned int createShaderProgram() {
    unsigned int vertexShader = createShader("./src/vertex_shader.glsl", GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader("./src/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to init glfw." << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "learnopengl2", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    unsigned int shader = createShaderProgram();
    unsigned int vao = createVAO();
    unsigned int vbo = createVBO();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void *) (0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * 3 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInputs(window);

        glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        unsigned int colorMultiplierLocation = glGetUniformLocation(shader, "colorMultiplier");
        glUniform1f(colorMultiplierLocation, sin(glfwGetTime()) / 2.f + 0.5f);
        glUseProgram(shader);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}