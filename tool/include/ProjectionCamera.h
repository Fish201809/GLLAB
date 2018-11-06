#pragma once




#include "camera.h"



#pragma warning( disable : 4244 )

class ProjectionCamera:public Camera
{
public:
	void update_vector();
	ProjectionCamera() {}

	virtual glm::mat4 get_matrix() override;

	virtual void keyfunCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			World_position(World_position() - Front() * speed_);
		}
		else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			World_position(World_position() + Front() * speed_);
		}
		else if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			World_position(World_position() + Right() * speed_);
		}
		else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			World_position(World_position() - Right() * speed_);
		}
		else if (key == GLFW_KEY_H && (action == GLFW_REPEAT || action == GLFW_PRESS)) {

		}	
	}

	virtual void scrollfunCallBack(GLFWwindow* window, double x, double y) override{
		//std::cout << "x: " << x << " y: " << y << std::endl;
		if (Fov() >= 1.0f && Fov() <= 45.0f)
			Fov(Fov() - y);
		if (Fov() <= 1.0f)
			Fov(1.0f);
		if (Fov() >= 45.0f)
			Fov(45.0f);

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

				float sensitivity = 0.05f;
				xoffset *= sensitivity;
				yoffset *= sensitivity;

				Yaw(Yaw() - xoffset);
				Pitch(Pitch() - yoffset);

				if (Pitch() > 89.0f)
					Pitch(89.0f);
				if (Pitch() < -89.0f)
					Pitch(-89.0f);

				update_vector();
		}
	}
	
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

