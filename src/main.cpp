#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

unsigned int HEIGHT = 600;
unsigned int WIDTH = 800;
const char* TITLE = "GAME";

void glfwWindowSizeCallback(GLFWwindow* window, int height, int width) {
	HEIGHT = height;
	WIDTH = width;
	glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow* window, int key, int action, int scancode, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
	if (!glfwInit()) {
		cerr << "glfwInit failed!" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
	if (!window) {
		cerr<<"Failed to create window"<<endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		cerr<<"Can't load GLAD!"<<endl;
		return -1;
	}
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "OPENGL " << GLVersion.major << "." << GLVersion.minor << endl;
	cout << "OPENGL VERSION: " << glGetString(GL_VERSION) << endl;

	glClearColor(1, 1, 1, 1);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

