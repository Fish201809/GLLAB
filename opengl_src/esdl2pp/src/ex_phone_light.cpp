#include "ex_phone_light.h"
#include "rfloor.h"

EXPhoneLight::EXPhoneLight() {
	floor_ = std::make_shared<RFloor>();
}

void EXPhoneLight::Init() {
	floor_->Init();
}

void EXPhoneLight::RenderGL(std::shared_ptr<ProjectionCamera> camera) {
	floor_->Render(camera);
}

void EXPhoneLight::RenderGUI() {
	
}
