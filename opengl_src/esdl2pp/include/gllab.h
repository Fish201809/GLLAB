#pragma once


#include "basic_loop.h"
#include "exobject.h"

class EXTessellation;
class RFloor;
class ShaderProgram;
class ProjectionCamera;

class GLLab : public BasicLoop
{
public:
	GLLab();
	virtual void Init() override;
	virtual void RenderGL() override;
	virtual void SetState() override;
	virtual void RenderGui() override;

	virtual void ProsessEvent(SDL_Event event) override;

	virtual void KeyEvent() override;
private:
	bool select_statue = true;
	bool wander_statue = true;

	std::shared_ptr<ProjectionCamera> camera = nullptr;
	const Uint8 *key_state_ = nullptr;

	std::shared_ptr<EXObject> exobject_ = nullptr;
};