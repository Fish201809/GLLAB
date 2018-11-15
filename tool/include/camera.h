#pragma once

#include "common.h"

class Camera
{
public:
	float speed_ = 3.0f;
	float speed_front_ = 10.0f;

	glm::vec3 Up() const { return up_; }
	void Up(glm::vec3 val) { up_ = val; }
	glm::vec3 Right() const { return right_; }
	void Right(glm::vec3 val) { right_ = val; }
	glm::vec3 Front() const { return front_; }
	void Front(glm::vec3 val) { front_ = val; }
	
	glm::vec3 World_position() const { return world_position_; }
	void World_position(glm::vec3 val) { world_position_ = val; }
public:
	virtual glm::mat4 get_vpmatrix() = 0;
	virtual glm::mat4 get_view_matrix() = 0;
	virtual glm::mat4 get_project_matrix() = 0;
private:
	glm::vec3 world_position_ = glm::vec3(0.0f, 1.0f, 5.0f);
	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right_ = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 front_ = glm::vec3(0.0f, 0.0f, 1.0f);
};
