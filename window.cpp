#include "GLFW/glfw3.h"
#include <string>
typedef unsigned int uint; 

int main() {
	const uint HEIGHT = 600;
	const uint WIDTH = 800;
	const string TITLE = "TEST"
	GLFWwindow* window;
	if (!glfwInit())
		return -1;
	window = glwfCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
