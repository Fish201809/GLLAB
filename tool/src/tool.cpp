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

ExampleTemplate::ExampleTemplate():ExampleTemplate("EXTemplate") {
	
}

ExampleTemplate::ExampleTemplate(std::string ex_name) {
	setting(ex_name);
}

ExampleTemplate::~ExampleTemplate() {
}

void ExampleTemplate::setting(std::string ex_name)
{
	glfwInit();
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, ex_name.c_str(), nullptr, nullptr);
	glfwSetWindowSizeCallback(window, windowSizeCallBack);
	//glfwSetKeyCallback(window, keyfunCallBack);
	glfwSetScrollCallback(window, scrollfunCallBack);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallBack);

	glfwMakeContextCurrent(window);
	gl3wInit();

	
}


void ExampleTemplate::init() {

}

void ExampleTemplate::run() {
	try {
		LoadResource();
		init();
		set_state();
		while (glfwWindowShouldClose(window) != GL_TRUE) {
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
		std::cout << e.what() << std::endl;
	}
}

void ExampleTemplate::LoadResource() {
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/tbasic.vert"),
									FileSystem::getPath("shaders/tbasic.frag")), "tbasic");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame.frag")), "frame");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame_blur.frag")), "frame_blur");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame_edge_detection.frag")), "frame_edge_detection");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame_grayscale.frag")), "frame_grayscale");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame_grayscale_widget.frag")), "frame_grayscale_widget");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame_kernel.frag")), "frame_kernel");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/frame.vert"),
									   FileSystem::getPath("shaders/frame_lnversion.frag")), "frame_lnversion");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/test.vert"),
									FileSystem::getPath("shaders/test.frag")), "test");
	ShaderLoader::LoadShaderProgram(std::make_unique<ShaderProgram>(FileSystem::getPath("shaders/cbasic.vert"),
									FileSystem::getPath("shaders/light_mul.frag")), "light_mul");
}

void ExampleTemplate::process_key(GLFWwindow *window) {
	
	if (glfwGetKey(window, GLFW_KEY_W)) {
		camera_->world_position_ -= camera_->front_ * camera_->speed_front_ * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		camera_->world_position_ += camera_->front_ * camera_->speed_front_ * deltaTime;
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

