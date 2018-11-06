#pragma once

#include "basic_loop.h"
#include "ProjectionCamera.h"
#include "texture2d.h"
#include "cube.h"
#include "shader_Loader.h"
#include "filesystem.h"
#include "plane.h"
#include "shader_Loader.h"
#include "shaderprogram.h"


class GLLab : public BasicLoop
{
public:
	GLLab() = default;
	virtual void RenderGL() override;
	virtual void SetState() override;
};