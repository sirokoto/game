#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "deps/glad/gl.h"
#include <string>
#include <iostream>
typedef unsigned int uint; 
using namespace std;

int main() {
	GLFWAPI glfwInit();
	const uint HEIGHT = 600;
	const uint WIDTH = 800;
	const char* TITLE = "WINDOW";
	GLFWwindow* window = GLFWAPI glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (window == NULL) {
		cout<<"Failed to create window"<<endl;
		GLFWAPI glfwTerminate();
		return -1;
	}
	GLFWAPI glfwMakeContextCurrent(window);
	while (!GLFWAPI glfwWindowShouldClose(window)) {
		GLFWAPI glfwPollEvents();
		GLFWAPI glClear(GL_COLOR_BUFFER_BIT);
		GLFWAPI glfwSwapBuffers(window);
	}
	GLFWAPI glfwDestroyWindow(window);
	GLFWAPI glfwTerminate();
	return 0;
}

