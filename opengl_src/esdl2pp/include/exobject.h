#pragma once

#include <gl/gl3w.h>
#include <memory>
class ProjectionCamera;

class EXObject
{
public:
	EXObject() = default;
	virtual void Init() = 0;
	virtual void RenderGL(std::shared_ptr<ProjectionCamera> camera) = 0;
	virtual void RenderGUI() = 0;
};
