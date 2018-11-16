#pragma once

#include "exobject.h"
#include "common.h"
#include "materials.h"

class ShaderProgram;

class EXLightMaterials : public EXObject
{
public:
	virtual void Init() override;


	virtual void RenderGL(std::shared_ptr<ProjectionCamera> camera) override;


	virtual void RenderGUI() override;

private:
	void GenerateShader();

private:
	std::shared_ptr<ShaderProgram> phone_shader_ = nullptr;
	std::shared_ptr<ShaderProgram> gourand_shader_ = nullptr;

	bool phone_gourand_flag = true;

	std::shared_ptr<ShaderProgram> light_shader_ = nullptr;

	GLuint cube_vao_;
	GLuint light_vao_;

	glm::vec3 light_color_ = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 cube_position_ = glm::vec3(0.0f, 0.0f, 0.0f);

	Material material_;
	LightAttr light_attr_;
};
