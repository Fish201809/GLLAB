#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderprogram.h"
#include "texture2d.h"


class Plane
{
public:
	explicit Plane(std::unique_ptr<Texture2D> texture);
	virtual void Render(ShaderProgram &shader_program);
	void set_model_matrix(glm::mat4 model_matrix);
private:
	virtual void Init();

	GLuint vao_;
	GLuint vbo_;

	std::unique_ptr<Texture2D> texture_ = nullptr;
	glm::mat4 model_matrix_ = glm::mat4(1.0f);
	glm::mat4 vp_matrix_ = glm::mat4(1.0f);

	std::shared_ptr<ShaderProgram> program_;
};