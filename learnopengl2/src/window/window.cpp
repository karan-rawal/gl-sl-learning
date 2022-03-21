#include "includes.h"
#include "window/window.h"

Window::Window(int width, int height, const char *title) {
    this->glfwInitStatus = glfwInit();
    if (!this->glfwInitStatus) {
        std::cout << "Failed to initialize glfw." << std::endl;
        this->dispose();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window) {
        std::cout << "Failed to create window." << std::endl;
        this->dispose();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
        this->dispose();
        return;
    }
}

void Window::show(void (*onUpdate)(Window *window)) {
    while(!glfwWindowShouldClose(window)) {
        onUpdate(this);
    }
}

void Window::setFramebufferSizeCallback(void (*sizeCallback)(GLFWwindow *window,int width, int height)) {
    glfwSetFramebufferSizeCallback(window, sizeCallback);
}

void Window::dispose() {
    if (this->window != NULL) {
        glfwDestroyWindow(window);
    }
    if (this->glfwInitStatus) {
        glfwTerminate();
    }
}