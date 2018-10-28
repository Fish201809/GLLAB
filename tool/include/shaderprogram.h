#pragma once
#include <gl/gl3w.h>
#include "native.h"
#include <string>

#include <glm/glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::string &vert_path, const std::string &frag_path, bool link_flag = true);
	void attach_vertex_shader(const std::string &path);
	void attach_fragment_shader(const std::string &path);

	bool set_uniform_mat4(const std::string &name, const glm::mat4 &mat);
	bool set_uniform_1i(const std::string &name, GLint texture_id);
	void link();
	void use();
	GLuint get_handle();

private:
	GLuint handle;
	GLuint vertex_shader_handle;
	GLuint fragment_shader_handle;
};