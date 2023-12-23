#include <GLFW/glfw3.h>
#include <string>
typedef unsigned int uint; 

int main() {
	const uint HEIGHT = 600;
	const uint WIDTH = 800;
	const string TITLE = "TEST"
	GLFWwindow* win;
	if (!glfwInit())
		return -1;
	win = glwfCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (!win) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	while (!glfwWindowShouldClose(win)){
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
