#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 800;

float vertices[] = {
    -0.5, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
};

void processInputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int createShader(char *shaderFile, unsigned int type) {
    unsigned int shader = glCreateShader(type);
    std::fstream shaderFileStream(shaderFile);
    std::stringstream buffer;
    buffer << shaderFileStream.rdbuf();
    std::string shaderSource = buffer.str();
    const char *shaderSourceChar = shaderSource.c_str();
    
    glShaderSource(shader, 1, &shaderSourceChar, NULL);
    glCompileShader(shader);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << shaderFile << " - ERROR\n" << infoLog << std::endl;
    }

    shaderFileStream.close();
    return shader;
}

unsigned int createShaderProgram(char *vertexShaderFile, char *fragmentShaderFile) {
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShader = createShader(vertexShaderFile, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader(fragmentShaderFile, GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "learnopengl2", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Faile to load glad." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    unsigned int shaderProgram = createShaderProgram("./src/vertex_shader.glsl", "./src/fragment_shader.glsl");
    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInputs(window);

        glClearColor(0.2f, 0.2f, 0.0f, 1.1f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}