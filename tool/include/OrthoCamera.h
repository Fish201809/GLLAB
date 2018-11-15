#pragma once

#include "camera.h"

#pragma warning( disable : 4244 )

class OrthoCamera : public Camera
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
	virtual glm::mat4 get_vpmatrix() override;

	virtual glm::mat4 get_project_matrix() override;


	virtual glm::mat4 get_view_matrix() override;

private:
	void update_vector();
};
