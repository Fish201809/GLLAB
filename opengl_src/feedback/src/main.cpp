#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include "native.h"
#include <iostream>
#include "shaderprogram.h"
#include "error.h"

using namespace std;

void ErrorCallBack(int error, const char *description) {
}

int main(int agrc, char *argv[]) {
	try {
		glfwSetErrorCallback(&ErrorCallBack);
		if (glfwInit() != GL_TRUE) {
			std::cerr << "glfw init error" << std::endl;
			return -1;
		}
		GLFWwindow *window = nullptr;
		if ((window = glfwCreateWindow(640, 480, "learn opengl", nullptr, nullptr)) == nullptr) {
			std::cerr << "create window error" << std::endl;
		}
		glfwMakeContextCurrent(window);
		gl3wInit();

		ShaderProgram shader_program;
		//shader_program.attach_fragment_shader("basic.frag");
		shader_program.attach_vertex_shader("basic.vert");
		shader_program.link();
		shader_program.use();

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		GLint inputAttrib = glGetAttribLocation(shader_program.get_handle(), "inValue");
		glEnableVertexAttribArray(inputAttrib);
		glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, false, 0, 0);
		GLuint tbo;
		glGenBuffers(1, &tbo);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_READ);

		glEnable(GL_RASTERIZER_DISCARD);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK, 0, tbo);
		glBeginTransformFeedback(GL_POINT);
		glDrawArrays(GL_POINT, 0, 5);
		glEndTransformFeedback();
		GLfloat feedback[5];
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK, 0, sizeof(feedback), feedback);
		std::cout << feedback[0] << " " << feedback[1] << " " << feedback[2] << " " << feedback[3] << " " << feedback[4] << std::endl;

		printf("%f %f %f %f %f\n", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);

		while (glfwWindowShouldClose(window) != GL_TRUE) {
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