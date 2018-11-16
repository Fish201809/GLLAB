#pragma once
#include <gl/gl3w.h>
#include <memory>
class ShaderProgram;

class RCube
{
public:
	RCube() = default;
	void Init();
	void RenderGL();

private:
	std::shared_ptr<ShaderProgram> GenerateShader();
	GLuint vao_;
	GLuint vbo_;
	std::shared_ptr<ShaderProgram> shader_program_ = nullptr;
};
