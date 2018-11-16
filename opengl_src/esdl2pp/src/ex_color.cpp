#include "ex_color.h"
#include "shaderprogram.h"
#include <vector>
#include "ProjectionCamera.h"

void EXColor::Init() {
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};
	unsigned int VBO;
	glGenVertexArrays(1, &cube_vao_);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cube_vao_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &light_vao_);
	glBindVertexArray(light_vao_);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	GenerateShader();
}

void EXColor::RenderGL(std::shared_ptr<ProjectionCamera> camera) {
	cube_shader_->use();
	cube_shader_->set_uniform_mat4("uModelMatrix", glm::mat4(1.0f));
	cube_shader_->set_uniform_mat4("uViewMatrix", camera->get_view_matrix());
	cube_shader_->set_uniform_mat4("uProjectMatrix", camera->get_project_matrix());
	cube_shader_->set_uniform_vec3("uObjectColor", cube_color_);
	cube_shader_->set_uniform_vec3("uLightColor", light_color_);
	glBindVertexArray(cube_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	light_shader_->use();
	light_shader_->set_uniform_mat4("uModelMatrix", glm::translate(glm::mat4(1.0f), light_position_) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)));
	light_shader_->set_uniform_mat4("uViewMatrix", camera->get_view_matrix());
	light_shader_->set_uniform_mat4("uProjectMatrix", camera->get_project_matrix());
	glBindVertexArray(light_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void EXColor::RenderGUI() {

}

void EXColor::GenerateShader() {
	std::string cube_vertex_shader =
		"#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"layout(location = 4) in vec3 vNormal;\n"
		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uViewMatrix;\n"
		"uniform mat4 uProjectMatrix;\n"
		"void main(){\n"
		"	gl_Position = uProjectMatrix * uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f);\n"
		"};\n";

	std::string cube_fragment_shader =
		"#version 450 core\n"
		"out vec4 Color;\n"
		"uniform vec3 uObjectColor;\n"
		"uniform vec3 uLightColor;\n"
		"void main(){\n"
		"	Color = vec4(uObjectColor * uLightColor, 1.0f);\n"
		"}\n";
	cube_shader_ = std::make_shared<ShaderProgram>();
	cube_shader_->attach_vertex_shader(cube_vertex_shader);
	cube_shader_->attach_fragment_shader(cube_fragment_shader);
	cube_shader_->link();

	std::string light_vertex_shader =
		"#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uViewMatrix;\n"
		"uniform mat4 uProjectMatrix;\n"
		"void main(){\n"
		"	gl_Position = uProjectMatrix * uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f);\n"
		"};\n";

	std::string light_fragment_shader =
		"#version 450 core\n"
		"out vec4 Color;\n"
		"void main(){\n"
		"	Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n";
	light_shader_ = std::make_shared<ShaderProgram>();
	light_shader_->attach_vertex_shader(light_vertex_shader);
	light_shader_->attach_fragment_shader(light_fragment_shader);
	light_shader_->link();
}
