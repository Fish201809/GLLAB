#pragma once

#include "native.h"



class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::string &vert_path, const std::string &frag_path, bool link_flag = true);
	void attach_vertex_shader_file(const std::string &path);
	void attach_fragment_shader_file(const std::string &path);
	void attach_tess_control_shader_file(const std::string &path);
	void attach_tess_evaluation_shader_file(const std::string &path);

	void attach_vertex_shader(const std::string &path);
	void attach_fragment_shader(const std::string &path);
	void attach_tess_control_shader(const std::string &path);
	void attach_tess_evaluation_shader(const std::string &path);



	bool set_uniform_mat4(const std::string &name, const glm::mat4 &mat);
	bool set_uniform_1i(const std::string &name, GLint texture_id);
	bool set_uniform_1ui(const std::string &name, GLuint texture_id);
	bool set_uniform_vec3(const std::string &name, float x, float y, float z);
	bool set_uniform_vec3(const std::string &name, glm::vec3 value);
	bool set_uniform_vec4(const std::string &name, float x, float y, float z, float w);
	bool set_uniform_1f(const std::string &name, GLfloat value);
	void link();
	void use();
	GLuint get_handle();

private:
	GLuint handle;
	GLuint vertex_shader_handle;
	GLuint fragment_shader_handle;
	GLuint tess_control_handle_;
	GLuint tess_evaluation_handle_;
};