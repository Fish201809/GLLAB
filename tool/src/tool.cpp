#include "tool.h"


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

ExampleTemplate::ExampleTemplate() {
	plane = std::make_shared<Plane>();
	setting();
}

void ExampleTemplate::setting() {
	glfwInit();
	window = glfwCreateWindow(800, 600, "learn opengl", nullptr, nullptr);
	glfwSetWindowSizeCallback(window, windowSizeCallBack);
	//glfwSetKeyCallback(window, keyfunCallBack);
	glfwSetScrollCallback(window, scrollfunCallBack);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallBack);

	glfwMakeContextCurrent(window);
	gl3wInit();
}


void ExampleTemplate::init() {
	plane->init();
}

void ExampleTemplate::display() {
	plane->display();
}

void ExampleTemplate::run() {
	try {
		init();
		glEnable(GL_DEPTH_TEST);
		while (glfwWindowShouldClose(window) != GL_TRUE) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			elapse_time = static_cast<float>(glfwGetTime());
			deltaTime = elapse_time - lastFrame;
			lastFrame = elapse_time;
			process_key(window);
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

void ExampleTemplate::process_key(GLFWwindow *window) {
	
	if (glfwGetKey(window, GLFW_KEY_W)) {
		camera_->world_position_ -= camera_->front_ * camera_->speed_ * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		camera_->world_position_ += camera_->front_ * camera_->speed_ * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		camera_->world_position_ += camera_->right_ * camera_->speed_ * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		camera_->world_position_ -= camera_->right_ * camera_->speed_ * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

