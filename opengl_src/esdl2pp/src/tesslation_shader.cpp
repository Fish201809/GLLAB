#include "tesslation_shader.h"
#include "filesystem.h"
#include "shaderprogram.h"

TesslationShader::TesslationShader() {
	static GLfloat vertices[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//声明一个面片的顶点数目
	glPatchParameteri(GL_PATCH_VERTICES, patch_vertex_num_);
	glEnableVertexAttribArray(0);
	shader_program_ = std::make_shared<ShaderProgram>();
	shader_program_->attach_vertex_shader(FileSystem::getPath("shaders/floor.vert"));
	shader_program_->attach_fragment_shader(FileSystem::getPath("shaders/floor.frag"));
	shader_program_->attach_tess_control_shader(FileSystem::getPath("shaders/floor.tesc"));
	shader_program_->attach_tess_evaluation_shader(FileSystem::getPath("shaders/floor.tese"));
	shader_program_->link();
}

void TesslationShader::Init() {

}

void TesslationShader::Render() {
	shader_program_->use();
	glBindVertexArray(vao_);
	glDrawArrays(GL_PATCHES, 0, 8);
}
