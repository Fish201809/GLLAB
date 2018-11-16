#pragma once

#include "exobject.h"
#include "common.h"

class ShaderProgram;

class EXColor: public EXObject
{
public:
	virtual void Init() override;


	virtual void RenderGL(std::shared_ptr<ProjectionCamera> camera) override;


	virtual void RenderGUI() override;
	
private:
	void GenerateShader();

private:
	std::shared_ptr<ShaderProgram> cube_shader_ = nullptr;
	std::shared_ptr<ShaderProgram> light_shader_ = nullptr;

	GLuint cube_vao_;
	GLuint light_vao_;

	glm::vec3 cube_color_ = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 light_color_ = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 cube_position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 light_position_ = glm::vec3(1.2f, 1.0f, 2.0f);
};