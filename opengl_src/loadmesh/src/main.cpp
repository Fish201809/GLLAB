#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderprogram.h"
#include "vgl.h"
#include "filesystem.h"
using namespace std;


static const GLfloat vbo_chess_vertex[] = {
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f, 0.5f,0.0f,
	-0.5f, -0.5f, 0.0f
};

GLuint vao, vbo;
GLuint fbo;
GLuint buffer;

void init() {
	
//	DoTheImportThing(FileSystem::getPath("model/nanosuit/nanosuit.obj"));
	ShaderProgram shader_program;
	shader_program.attach_vertex_shader("basic.vert");
	shader_program.attach_fragment_shader("basic.frag");
	shader_program.link();
	shader_program.use();

	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vbo_chess_vertex), vbo_chess_vertex, 0);
	
	glCreateVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void display() {
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(int agrc, char *argv[]) {
	try {
		glfwInit();
			
		GLFWwindow *window = glfwCreateWindow(640, 480, "learn opengl", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		gl3wInit();
		init();
		while (glfwWindowShouldClose(window) != GL_TRUE) {
			display();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	

	return 0;
}