#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void onFramebufferSize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	// Initialize glfwInit
	glfwInit();

	// Hint glfw which opengl version we are goona use.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Hint glfw we are using only core profile.
	// So we have access to only modern functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a glfw window and do the error handling.
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "learnopengl.com", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create window." << endl;
		glfwTerminate();
		return -1;
	}
	// Tell gltf to use the window as current context.
	glfwMakeContextCurrent(window);

	// tell glad to use glfwGetProcAddress to get the OS specific gl loaders.
	// we can also use gladLoadGL() but not sure which is the correct way.
	// we need to do this before doing anything related to open gl.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize glad." << endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, onFramebufferSize);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// The main window loop.
	while (!glfwWindowShouldClose(window)) {

		// OpenGL operations.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Tell glfw to swap front buffer with back buffer.
		glfwSwapBuffers(window);

		// Process all pending events. Without this no events will be triggered.
		glfwPollEvents();
		// Handle the event.
		processInput(window);
	}

	// finally, destroy the window and terminate glfw.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}