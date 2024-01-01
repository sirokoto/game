#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

GLfloat point[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};
GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};
const char* vertex_shader =
"#version 400\n"
"layout(location = 0) in vec3 vertex_pos;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"	color = vertex_color;"
"	gl_Position = vec4(vertex_pos, 1.0);"
"}";

const char* frag_shader =
"#version 400\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"	frag_color = vec4(color, 1.0);"
"}";

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

	glClearColor(0, 0, 0, 1);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &frag_shader, nullptr);
	glCompileShader(fs);

	GLuint prog_shader = glCreateProgram();
	glAttachShader(prog_shader, vs);
	glAttachShader(prog_shader, fs);
	glLinkProgram(prog_shader);

	glDeleteShader(vs);
	glDeleteShader(fs);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(prog_shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

