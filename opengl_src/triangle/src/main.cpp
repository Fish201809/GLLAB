#include "tool.h"

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
	ShaderProgram shader_program;
	shader_program.attach_vertex_shader("tbasic.vert");
	shader_program.attach_fragment_shader("tbasic.frag");
	shader_program.link();
	shader_program.use();

	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vbo_chess_vertex), vbo_chess_vertex, 0);
	//	glNamedBufferStorage(vbo, sizeof(vbo_chess_vertex), vbo_chess_vertex, 0);

	glCreateVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//feedback
	glCreateTransformFeedbacks(1, &fbo);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, fbo);
	if (glIsTransformFeedback(fbo)) {
		std::cout << "is feedback" << std::endl;
	}
	else {
		std::cout << "is not feedback" << std::endl;
	}
	GLuint buffer;
	glCreateBuffers(1, &buffer);
	glNamedBufferStorage(buffer, 1024 * 1024, NULL, 0);
	glTransformFeedbackBufferRange(fbo, 0, buffer, 0, 512 * 1024);
	glTransformFeedbackBufferRange(fbo, 1, buffer, 512 * 1024, 512 * 1024);
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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