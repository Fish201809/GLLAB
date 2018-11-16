#include "rcube.h"
#include <string>
#include "shaderprogram.h"

static const GLfloat cube__vertex[]{
	 -5.0f, -5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
	 5.0f, -5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
	 5.0f,  5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
	 5.0f,  5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
	-5.0f,  5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
	-5.0f, -5.0f, -5.0f,  0.0f,  0.0f, -1.0f,

	-5.0f, -5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
	 5.0f, -5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
	 5.0f,  5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
	 5.0f,  5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
	-5.0f,  5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
	-5.0f, -5.0f,  5.0f,  0.0f,  0.0f,  1.0f,

	-5.0f,  5.0f,  5.0f, -1.0f,  0.0f,  0.0f,
	-5.0f,  5.0f, -5.0f, -1.0f,  0.0f,  0.0f,
	-5.0f, -5.0f, -5.0f, -1.0f,  0.0f,  0.0f,
	-5.0f, -5.0f, -5.0f, -1.0f,  0.0f,  0.0f,
	-5.0f, -5.0f,  5.0f, -1.0f,  0.0f,  0.0f,
	-5.0f,  5.0f,  5.0f, -1.0f,  0.0f,  0.0f,

	 5.0f,  5.0f,  5.0f,  1.0f,  0.0f,  0.0f,
	 5.0f,  5.0f, -5.0f,  1.0f,  0.0f,  0.0f,
	 5.0f, -5.0f, -5.0f,  1.0f,  0.0f,  0.0f,
	 5.0f, -5.0f, -5.0f,  1.0f,  0.0f,  0.0f,
	 5.0f, -5.0f,  5.0f,  1.0f,  0.0f,  0.0f,
	 5.0f,  5.0f,  5.0f,  1.0f,  0.0f,  0.0f,

	-5.0f, -5.0f, -5.0f,  0.0f, -1.0f,  0.0f,
	 5.0f, -5.0f, -5.0f,  0.0f, -1.0f,  0.0f,
	 5.0f, -5.0f,  5.0f,  0.0f, -1.0f,  0.0f,
	 5.0f, -5.0f,  5.0f,  0.0f, -1.0f,  0.0f,
	-5.0f, -5.0f,  5.0f,  0.0f, -1.0f,  0.0f,
	-5.0f, -5.0f, -5.0f,  0.0f, -1.0f,  0.0f,

	-5.0f,  5.0f, -5.0f,  0.0f,  1.0f,  0.0f,
	 5.0f,  5.0f, -5.0f,  0.0f,  1.0f,  0.0f,
	 5.0f,  5.0f,  5.0f,  0.0f,  1.0f,  0.0f,
	 5.0f,  5.0f,  5.0f,  0.0f,  1.0f,  0.0f,
	-5.0f,  5.0f,  5.0f,  0.0f,  1.0f,  0.0f,
	-5.0f,  5.0f, -5.0f,  0.0f,  1.0f,  0.0f
};

void RCube::Init() {
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube__vertex), cube__vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(4);
	shader_program_ = GenerateShader();
}

void RCube::RenderGL() {
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

std::shared_ptr<ShaderProgram> RCube::GenerateShader() {
	std::string vertex_shader =
		"#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"layout(location = 4) in vec3 vNormal;\n"
		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uViewMatrix;\n"
		"uniform mat4 uProjectMatrix;\n"
		"void main(){\n"
		"	gl_Position = uProjectMatrix * uViewMatrix * uModelMatrix * vPosition;\n"
		"};\n";

	std::string fragment_shader =
		"#version 450 core\n"
		"out vec3 fColor;\n"
		"void main(){\n"
		"fColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n";
	std::shared_ptr<ShaderProgram> shader_program = std::make_shared<ShaderProgram>();
	shader_program->attach_vertex_shader(vertex_shader);
	shader_program_->attach_fragment_shader(fragment_shader);
	shader_program_->link();
	return shader_program_;
}




















