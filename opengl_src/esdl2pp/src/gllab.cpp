#include "gllab.h"
#include "ProjectionCamera.h"
#include "texture2d.h"
#include "cube.h"
#include "shader_Loader.h"
#include "filesystem.h"
#include "plane.h"
#include "shader_Loader.h"
#include "shaderprogram.h"
#include "Tessellation.h"
#include "floor.h"
#include "PhoneLight.h"

GLLab::GLLab() {
	camera = std::make_shared<ProjectionCamera>();
	key_state_ = SDL_GetKeyboardState(nullptr);

    exobject_ = std::make_shared<PhoneLight>();
}

void GLLab::Init() {
	exobject_->Init();
}

void GLLab::RenderGL() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	exobject_->RenderGL(camera);
}

void GLLab::SetState() {
	glEnable(GL_DEPTH_TEST);
}

void GLLab::RenderGui() {
	__super::RenderGui();
	exobject_->RenderGUI();

	ImGui::Begin("example switch");
	{
		const char* items[] = { "PhoneLight",  "Tessellation"};
		static int item_current = 0;
		if (ImGui::Combo("primitype", &item_current, items, IM_ARRAYSIZE(items))) {
			if (item_current == 0) {
				exobject_ = std::make_shared<PhoneLight>();
				exobject_->Init();
			}
			else if (item_current == 1) {
				exobject_ = std::make_shared<Tessellation>();
				exobject_->Init();
			}
		}
	}
	ImGui::End();
}

void GLLab::ProsessEvent(SDL_Event event) {
	if (event.type == SDL_MOUSEWHEEL) {

		float fov = camera->Fov();
		fov = fov + event.wheel.y;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 89.0f)
			fov = 89.0f;
		camera->Fov(fov);
	}

	if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_BUTTON_LEFT) {
		static float xoffset = 0.0f;
		static float yoffset = 0.0f;
		static float speed = 3.0f;
		xoffset -= event.motion.xrel * speed;
		yoffset += event.motion.yrel * speed;
		float pitch = glm::radians(yoffset);
		float yaw = glm::radians(xoffset);
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		else if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		camera->Pitch(pitch);
		camera->Yaw(yaw);
		camera->update_vector();
	}
}

void GLLab::KeyEvent() {
	glm::vec3 position = camera->World_position();
	glm::vec3 front = camera->Front();
	glm::vec3 right = camera->Right();
	if (key_state_[SDL_SCANCODE_W] == SDL_TRUE) {
		position -= 0.2f * front;
		camera->World_position(position);
	}
	if (key_state_[SDL_SCANCODE_S] == SDL_TRUE) {
		position += 0.2f * front;
		camera->World_position(position);
	}
	if (key_state_[SDL_SCANCODE_D] == SDL_TRUE) {
		position -= 0.2f * right;
		camera->World_position(position);
	}
	if (key_state_[SDL_SCANCODE_A] == SDL_TRUE) {
		position += 0.2f * right;
		camera->World_position(position);
	}
}
