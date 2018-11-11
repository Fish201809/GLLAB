#include "gllab.h"
#include "ProjectionCamera.h"
#include "texture2d.h"
#include "cube.h"
#include "shader_Loader.h"
#include "filesystem.h"
#include "plane.h"
#include "shader_Loader.h"
#include "shaderprogram.h"
#include "Tessellation.h"



GLLab::GLLab() {
	floor_.reset(new Tessellation);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLLab::Init() {
	floor_->Init();
}

void GLLab::RenderGL() {
	glClear(GL_DEPTH_BUFFER_BIT);
	floor_->Render();
}

void GLLab::SetState() {
	glEnable(GL_DEPTH_TEST);
}

void GLLab::RenderGui() {
	floor_->GenerateGui();
}
