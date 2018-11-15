#include "floor.h"
#include "shaderprogram.h"
#include "texture2d.h"
#include "filesystem.h"
#include "ProjectionCamera.h"

void Floor::Init() {
	static GLfloat vertex[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,

		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	shader_program_ = GenerateShader();
	texture2d_ = std::make_shared<Texture2D>(FileSystem::getPath("Image/chess.jpg"));
}


void Floor::Render(std::shared_ptr<ProjectionCamera> camera) {
	texture2d_->bind();
	shader_program_->use();
	glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 1.0f));
	//glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 vp_matrix = camera->get_vpmatrix();
	shader_program_->set_uniform_mat4("model_matrix", rotate_matrix * scale_matrix);
	shader_program_->set_uniform_mat4("vp_matrix", vp_matrix);
	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

std::shared_ptr<ShaderProgram> Floor::GenerateShader() {
	std::string vertex_shader = {
		"#version 450 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec2 vCoord;\n"
		"uniform mat4 model_matrix;"
		"uniform mat4 vp_matrix;"
		"out vec2 fCoord;\n"
		"void main(){\n"
		"	gl_Position = vp_matrix * model_matrix * vec4(position, 1.0f);\n"
		"	fCoord = vCoord;\n"
		"}\n"
	};

	std::string fragment_shader = {
		"#version 450 core\n"
		"in vec2 fCoord;\n"
		"out vec4 Color;\n"
		"uniform sampler2D text_0;\n"
		"void main(){\n"
		"	Color = texture(text_0, fCoord);\n"
		"}\n"
	};

	std::shared_ptr<ShaderProgram> shader_program = std::make_shared<ShaderProgram>();
	shader_program->attach_vertex_shader(vertex_shader);
	shader_program->attach_fragment_shader(fragment_shader);
	shader_program->link();
	return shader_program;
}
