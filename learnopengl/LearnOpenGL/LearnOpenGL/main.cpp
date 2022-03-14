#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "learnopengl.com", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window.";
	}
	glfwMakeContextCurrent(window);


	while (true) {

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}