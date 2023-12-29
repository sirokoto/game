#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>

using namespace std;

int main(void) {
	glfwInit();
	const unsigned int HEIGHT = 600;
	const unsigned int WIDTH = 800;
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
		//glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

