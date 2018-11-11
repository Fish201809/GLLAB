#pragma once


#include "basic_loop.h"

class Tessellation;
class ShaderProgram;

class GLLab : public BasicLoop
{
public:
	GLLab();
	virtual void Init() override;
	virtual void RenderGL() override;
	virtual void SetState() override;
	virtual void RenderGui() override;
private:
	
	//细分着色器
	std::shared_ptr<Tessellation> floor_ = nullptr;
};