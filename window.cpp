#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "deps/glad/gl.h"
#include <string>
#include <iostream>

typedef unsigned int uint; 
using namespace std;

int main() {
	glfwInit();
	const uint HEIGHT = 600;
	const uint WIDTH = 800;
	const char* TITLE = "WINDOW";
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (window == NULL) {
		cout<<"Failed to create window"<<endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

