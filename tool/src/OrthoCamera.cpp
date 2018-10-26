#include "OrthoCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


void OrthoCamera::update_vector() {
	float y = glm::sin(glm::radians(pitch_) ) * 1.0f;
	float x = glm::cos(glm::radians(pitch_) ) * glm::sin(glm::radians(yaw_));
	float z = glm::cos(glm::radians(pitch_)) * glm::cos(glm::radians(yaw_));
	front_ =  glm::normalize(glm::vec3(x, y, z));
	right_ = glm::normalize(glm::cross(front_, WORLD_UP));
	up_ = -glm::normalize(glm::cross(front_, right_));

}

glm::mat4 OrthoCamera::get_matrix()
{
	//glm::vec3 target = world_position_ + front_ * distance_;
	//std::cout << "position : [ x: " << world_position_.x << ", y: " << world_position_.y << ", z: " << world_position_.z << std::endl;
	//std::cout << "target: [ x: " << target.x << ", y: " << target.y << ", z: " << target.z << std::endl;
	//std::cout << "up: [ x: " << up_.x << ", y: " << up_.y << ", z: " << up_.z << std::endl;

	//return glm::ortho(-harf_width_, harf_width_, -harf_height_, harf_height_) * 
	return glm::ortho(-harf_width_, harf_width_, -harf_height_, harf_height_, 0.1f, 1000.0f) * glm::lookAt(world_position_, world_position_ - front_ * distance_, up_);
}
