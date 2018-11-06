#include "ProjectionCamera.h"


glm::mat4 ProjectionCamera::get_matrix() {
	return get_project_matrix() * get_view_matrix();
}

glm::mat4 ProjectionCamera::get_project_matrix() {
	return glm::perspective(glm::radians(Fov()), width / height, 0.1f, 1000.0f);
}

glm::mat4 ProjectionCamera::get_view_matrix() {
	return glm::lookAt(World_position(), World_position() - Front() * distance_, Up());;
}

void ProjectionCamera::update_vector() {
	float y = glm::sin(glm::radians(Pitch())) * 1.0f;
	float x = glm::cos(glm::radians(Pitch())) * glm::sin(glm::radians(Yaw()));
	float z = glm::cos(glm::radians(Pitch())) * glm::cos(glm::radians(Yaw()));
	Front(glm::normalize(glm::vec3(x, y, z)));
	Right(glm::normalize(glm::cross(Front(), WORLD_UP)));
	Up(-glm::normalize(glm::cross(Front(), Right())));
}