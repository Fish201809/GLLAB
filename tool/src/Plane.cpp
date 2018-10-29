#include "Plane.h"
#include "tool.h"
#include "filesystem.h"


extern std::shared_ptr<Camera> camera_;


Plane::Plane(std::unique_ptr<Texture2D> texture) {
	texture_ = std::move(texture);
	Init();
}

void Plane::Render(ShaderProgram &shader_program)
{
	shader_program.use();
	shader_program.set_uniform_mat4("vp_matrix", camera_->get_matrix());
	shader_program.set_uniform_mat4("model_matrix", model_matrix_);
	glBindVertexArray(vao_);
	glActiveTexture(GL_TEXTURE0);
	texture_->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Plane::set_model_matrix(glm::mat4 model_matrix) {
	model_matrix_ = model_matrix;
}

void Plane::Init() {
	static const GLfloat cube_data[][3] = {
			{-5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, 5.0f},
			{-5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, 5.0f},
			{-5.0f, 0.0f, 5.0f}
	};
	static const GLfloat plane_cord[][2] = {
		{0.0f, 0.0f}, 
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
	};
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glNamedBufferStorage(vbo_, sizeof(cube_data) + sizeof(plane_cord), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_, 0, sizeof(cube_data), cube_data);
	glNamedBufferSubData(vbo_, sizeof(cube_data), sizeof(plane_cord), plane_cord);


	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)sizeof(cube_data));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
