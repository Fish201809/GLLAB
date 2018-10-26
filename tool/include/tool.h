#pragma once

#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include "shaderprogram.h"
#include "OrthoCamera.h"
#include "ProjectionCamera.h"



using namespace std;

std::shared_ptr<Camera> camera_ = std::make_shared<ProjectionCamera>();

void keyfunCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	camera_->keyfunCallBack(window, key, scancode, action, mods);
}

void scrollfunCallBack(GLFWwindow* window, double x, double y) {
	camera_->scrollfunCallBack(window, x, y);
}

void mouseCallBack(GLFWwindow* window, double xpos, double ypos) {
	camera_->mouseCallBack(window, xpos, ypos);
}

void windowSizeCallBack(GLFWwindow* window, int width, int height) {
	//std::cout << "width: " << width << " height: " << height << std::endl;
	glViewport(0, 0, width, height);
}

class ExampleTemplate
{
public:
	ExampleTemplate() {
		setting();
	}
	
	GLFWwindow *window = nullptr;
	void setting() {
		glfwInit();
		window = glfwCreateWindow(640, 480, "learn opengl", nullptr, nullptr);
		glfwSetWindowSizeCallback(window, windowSizeCallBack);
		glfwSetKeyCallback(window, keyfunCallBack);
		glfwSetScrollCallback(window, scrollfunCallBack);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window,mouseCallBack);

		glfwMakeContextCurrent(window);
		gl3wInit();
	}

public:
	virtual void init();
	virtual void display();
	virtual void run();


};



void ExampleTemplate::init() {

}

void ExampleTemplate::display() {

}

void ExampleTemplate::run() {
	try {
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
}
