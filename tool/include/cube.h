#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderprogram.h"
#include "texture2d.h"



class Cube
{
public:
	Cube(glm::vec3 color, std::unique_ptr<Texture2D> texture);
	explicit Cube(std::unique_ptr<Texture2D> texture);
	void set_model_matrix(glm::mat4 model_matrix);
	virtual void Render(ShaderProgram &shader_program);
private:
	virtual void Init();

	GLuint ebo_;
	GLuint vao_;
	GLuint vbo_;
	std::unique_ptr<Texture2D> texture_;
	glm::mat4 model_matrix_ = glm::mat4(1.0f);
	glm::mat4 vp_matrix_ = glm::mat4(1.0f);
};


