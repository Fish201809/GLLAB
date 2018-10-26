#include "ProjectionCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 ProjectionCamera::get_matrix() {
	glm::mat4 projection = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f) * glm::lookAt(world_position_, world_position_ - front_ * distance_, up_);;
	return projection;
}

void ProjectionCamera::update_vector() {
	float y = glm::sin(glm::radians(pitch_)) * 1.0f;
	float x = glm::cos(glm::radians(pitch_)) * glm::sin(glm::radians(yaw_));
	float z = glm::cos(glm::radians(pitch_)) * glm::cos(glm::radians(yaw_));
	front_ = glm::normalize(glm::vec3(x, y, z));
	right_ = glm::normalize(glm::cross(front_, WORLD_UP));
	up_ = -glm::normalize(glm::cross(front_, right_));
}
