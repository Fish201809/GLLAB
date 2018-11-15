#pragma once

#include "exobject.h"

class Floor;

class PhoneLight: public EXObject
{
public:
	PhoneLight();
	virtual void Init() override;


	virtual void RenderGL(std::shared_ptr<ProjectionCamera> camera) override;


	virtual void RenderGUI() override;

private:
	std::shared_ptr<Floor> floor_ = nullptr;
};