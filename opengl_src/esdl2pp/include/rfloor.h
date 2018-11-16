

#pragma once

#include "common.h"

class Texture2D;
class ShaderProgram;
class ProjectionCamera;

class RFloor
{
public:
	void Init();
	void Render(std::shared_ptr<ProjectionCamera> camera);
	std::shared_ptr<ShaderProgram> GenerateShader();
private:
	std::shared_ptr<ShaderProgram> shader_program_ = nullptr;
	std::shared_ptr<Texture2D> texture2d_ = nullptr;
	GLuint vao_;
	GLuint vbo_;
};