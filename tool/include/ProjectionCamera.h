#pragma once




#include "camera.h"



#pragma warning( disable : 4244 )

class ProjectionCamera:public Camera
{
public:
	void update_vector();
	ProjectionCamera() {}

	virtual glm::mat4 get_vpmatrix() override;

	virtual glm::mat4 get_project_matrix() override;

	virtual glm::mat4 get_view_matrix() override;
	float Fov() const { return fov; }
	void Fov(float val) { fov = val; }
	float Pitch() const { return pitch_; }
	void Pitch(float val) { pitch_ = val; }
	float Yaw() const { return yaw_; }
	void Yaw(float val) { yaw_ = val; }
private:
	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw_ = 0.0f;		//偏航角
	float pitch_ = 0.0f;	//俯仰角

	float fov = 30.0f;
	float width = 800.0f;
	float height = 600.0f;

	float distance_ = 5000.0f;

};

