#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void ErrorCallBack(int error, const char *description) {

}

int main(int agrc, char *argv[]) {

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
	while (glfwWindowShouldClose(window) != GL_TRUE) {

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}