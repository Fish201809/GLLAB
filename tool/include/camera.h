#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	virtual glm::mat4 get_matrix() = 0;

	virtual void keyfunCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

	virtual void scrollfunCallBack(GLFWwindow* window, double x, double y) = 0;

	virtual void mouseCallBack(GLFWwindow* window, double xpos, double ypos) = 0;
};
