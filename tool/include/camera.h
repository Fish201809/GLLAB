#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	float speed_ = 50.0f;
	float speed_front_ = 130.0f;

	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right_ = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 front_ = glm::vec3(0.0f, 0.0f, 1.0f);

	
	glm::vec3 World_position() const { return world_position_; }
	void World_position(glm::vec3 val) { world_position_ = val; }
public:
	virtual glm::mat4 get_matrix() = 0;
	virtual glm::mat4 get_view_matrix() = 0;
	virtual glm::mat4 get_project_matrix() = 0;

	virtual void keyfunCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

	virtual void scrollfunCallBack(GLFWwindow* window, double x, double y) = 0;

	virtual void mouseCallBack(GLFWwindow* window, double xpos, double ypos) = 0;
private:
	glm::vec3 world_position_ = glm::vec3(-10.0f, 15.0f, 100.0f);
};
