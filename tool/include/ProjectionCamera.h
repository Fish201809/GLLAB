#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "camera.h"


class ProjectionCamera:public Camera
{
public:

	ProjectionCamera() {
	}

	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw_ = 0.0f;		//偏航角
	float pitch_ = 0.0f;	//俯仰角


	float fov = 30.0f;
	float width = 800.0f;
	float height = 600.0f;

	float distance_ = 1000.0f;
	float speed_ = 1.0f;

	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right_ = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 front_ = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 world_position_ = glm::vec3(0.0f, 0.0f, 10.0f);

	virtual glm::mat4 get_matrix() override;

	virtual void keyfunCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
			if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
				world_position_ -= front_ * speed_;
			}
			else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
				world_position_ += front_ * speed_;
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

	virtual void scrollfunCallBack(GLFWwindow* window, double x, double y) override{
		//std::cout << "x: " << x << " y: " << y << std::endl;
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= y;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;

	}

	virtual void mouseCallBack(GLFWwindow* window, double xpos, double ypos) override{
		//std::cout << "x: " << xpos << " y: " << ypos << std::endl;
	
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

				float sensitivity = 0.05;
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
private:
	void update_vector();
};

