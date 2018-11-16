#pragma once

#include "exobject.h"

class RFloor;

class EXPhoneLight: public EXObject
{
public:
	EXPhoneLight();
	virtual void Init() override;


	virtual void RenderGL(std::shared_ptr<ProjectionCamera> camera) override;


	virtual void RenderGUI() override;

private:
	std::shared_ptr<RFloor> floor_ = nullptr;
};


