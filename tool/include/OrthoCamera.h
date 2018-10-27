#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "camera.h"

#pragma warning( disable : 4244 )

class OrthoCamera: public Camera
{
public:
	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	OrthoCamera(float harf_width, float harf_height, bool control_enable) {
		harf_height_ = harf_height;
		harf_width_ = harf_width;
		control_enable_ = control_enable;
	}
	OrthoCamera() :OrthoCamera(10.0f, 10.0f, false) {

	}
	bool control_enable_ = false;
	float yaw_ = 0.0f;		//偏航角
	float pitch_ = 0.0f;	//俯仰角

	float harf_width_ = 10.0f;
	float harf_height_ = 10.0f;

	float distance_ = 1000.0f;
	virtual glm::mat4 get_matrix() override;

	virtual void keyfunCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (control_enable_) {
			if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
				world_position_ += up_ * speed_;
			}
			else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
				world_position_ -= up_ * speed_;
			}
			else if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
				world_position_ += right_ * speed_;
			}
			else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
				world_position_ -= right_ * speed_;
			}
			else if (key == GLFW_KEY_H && (action == GLFW_REPEAT || action == GLFW_PRESS)) {

			}
		}
		
	}

	virtual void scrollfunCallBack(GLFWwindow* window, double x, double y) override {
		//std::cout << "x: " << x << " y: " << y << std::endl;
		if (control_enable_) {
			harf_height_ = static_cast<float>(harf_height_ + y);
			harf_width_ = static_cast<float>(harf_width_ + y);
		}
	}

	virtual void mouseCallBack(GLFWwindow* window, double xpos, double ypos) override {
		//std::cout << "x: " << xpos << " y: " << ypos << std::endl;
		if (control_enable_) {
			static bool flag = true;
			static float last_x = xpos;
			static float last_y = ypos;
			if (flag) {
				flag = false;
			}
			else {
				float xoffset = xpos - last_x;
				float yoffset = last_y - ypos;
				last_x = xpos;
				last_y = ypos;

				float sensitivity = 0.05f;
				xoffset *= sensitivity;
				yoffset *= sensitivity;

				yaw_ -= xoffset;
				pitch_ -= yoffset;

				if (pitch_ > 89.0f)
					pitch_ = 89.0f;
				if (pitch_ < -89.0f)
					pitch_ = -89.0f;

				update_vector();
			}
		}
	}
private:
	void update_vector();
};
