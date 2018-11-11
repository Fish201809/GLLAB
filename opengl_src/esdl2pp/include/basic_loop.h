#pragma once

#include "common.h"
#pragma warning( disable : 4244 )

using namespace std;

class ProjectionCamera;

class BasicLoop
{
public:
	BasicLoop();
	virtual ~BasicLoop();
public:
	virtual void SetState();
	virtual void Init();
	virtual void Run();
	virtual void RenderGL();
	virtual void RenderGui();
	virtual void LoadResource();
	virtual void ProsessEvent(SDL_Event event);
	virtual void KeyEvent();

private:
	bool show_demo_window_ = true;
	bool show_another_window_ = false;
	ImVec4 clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool done_ = false;
	SDL_Window *window_ = nullptr;
	SDL_GLContext gl_context_;
	std::shared_ptr<ProjectionCamera> camera = nullptr;
	const Uint8 *key_state_ = nullptr;
};
