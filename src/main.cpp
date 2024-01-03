#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

using namespace std;

GLfloat point[] = {
	-0.5f, 0.5f, 0.0f,  //0
	0.5f, 0.5f, 0.0f,   //2
	-0.5f, -0.5f, 0.0f, //1
//	0.5f, -0.5f, 0.0f,  //3
};
GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,   //red
	0.0f, 1.0f, 0.0f,   //green
	0.0f, 0.0f, 1.0f,   //blue
//	1.0f, 1.0f, 1.0f    //white
};
//const GLuint indices[] = {0, 1, 2, 2, 1, 3};

unsigned int HEIGHT = 600;
unsigned int WIDTH = 600;
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

int main(int argc, char** argv) {
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

	glClearColor(0, 0, 0, 1);
	{
		ResourceManager resourceManager(argv[0]);
		auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shader/vertexShader.txt", "res/shader/fragmentShader.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't Create Shader Program: " << "DefaultShader" << std::endl;
			return -1;
		}
		
		GLuint points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}

