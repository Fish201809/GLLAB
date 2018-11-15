#include "PhoneLight.h"
#include "floor.h"

PhoneLight::PhoneLight() {
	floor_ = std::make_shared<Floor>();
}

void PhoneLight::Init() {
	floor_->Init();
}

void PhoneLight::RenderGL(std::shared_ptr<ProjectionCamera> camera) {
	floor_->Render(camera);
}

void PhoneLight::RenderGUI() {
	
}
