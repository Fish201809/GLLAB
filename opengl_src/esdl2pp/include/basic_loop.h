#pragma once

#include "common.h"
#pragma warning( disable : 4244 )

using namespace std;


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

protected:
	bool opengl_status_window_ = true;
	bool show_another_window_ = false;
	ImVec4 clear_color_ = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
	
	bool done_ = false;
	SDL_Window *window_ = nullptr;
	SDL_GLContext gl_context_;
	
};
