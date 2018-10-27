#include "shaderprogram.h"
#include "error.h"
#include <vector>

static void check_program_status(GLuint program, GLenum what_to_check) {
	GLint status;
	glGetProgramiv(program, what_to_check, &status);

	if (status != GL_TRUE) {
		GLint loglen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglen);

		std::vector<char> infolog(loglen);
		glGetProgramInfoLog(program, loglen, nullptr, infolog.data());

		const char *what_str = [=] {
			switch (what_to_check) {
				case GL_LINK_STATUS:
					return "linking";
				case GL_VALIDATE_STATUS:
					return "validation";
				case GL_COMPILE_STATUS:
					return "compilation";
				default:
					return "unknown shader creation task";
			}
		}();
		std::string info = "";
		info = info + "OpenGL shader program " + what_str + " failed:\n" + infolog.data();
		throw Error(info);
	}
}

ShaderProgram::ShaderProgram() {
	handle = glCreateProgram();
}

void ShaderProgram::attach_vertex_shader(const std::string &path) {
	Native native(path);

	// allocate shader in opengl
	vertex_shader_handle = glCreateShader(GL_VERTEX_SHADER);

	// load shader source
	std::string core = native.read().c_str();
	const char* data = core.c_str();
	glShaderSource(vertex_shader_handle, 1, &data, nullptr);

	// compile shader source
	glCompileShader(vertex_shader_handle);

	// check compiliation result
	GLint status;
	glGetShaderiv(vertex_shader_handle, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv(vertex_shader_handle, GL_INFO_LOG_LENGTH, &loglen);

		std::vector<char> infolog(loglen);
		glGetShaderInfoLog(vertex_shader_handle, loglen, nullptr, infolog.data());

		std::string info = "";
		info = info + "Failed to compiler vertex shader:\n" + infolog.data();
		throw Error(info);
	}
	glAttachShader(handle, vertex_shader_handle);
}

void ShaderProgram::attach_fragment_shader(const std::string &path) {
	Native native(path);

	// allocate shader in opengl
	fragment_shader_handle = glCreateShader(GL_FRAGMENT_SHADER);

	// load shader source
	std::string core = native.read().c_str();
	const char* data = core.c_str();
	glShaderSource(fragment_shader_handle, 1, &data, nullptr);

	// compile shader source
	glCompileShader(fragment_shader_handle);

	// check compiliation result
	GLint status;
	glGetShaderiv(fragment_shader_handle, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv(fragment_shader_handle, GL_INFO_LOG_LENGTH, &loglen);

		std::vector<char> infolog(loglen);
		glGetShaderInfoLog(fragment_shader_handle, loglen, nullptr, infolog.data());

		std::string info = std::string() + "Failed to compiler fragment shader:\n" + infolog.data();
		throw Error(info);
	}
	glAttachShader(handle, fragment_shader_handle);
}

bool ShaderProgram::set_uniform_mat4(const std::string &name, const glm::mat4 &mat) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniformMatrix4fv(location_id, 1, GL_FALSE, &mat[0][0]);
	return true;
}

void ShaderProgram::link() {
	glLinkProgram(handle);
	check_program_status(handle, GL_LINK_STATUS);

	glValidateProgram(handle);
	check_program_status(handle, GL_VALIDATE_STATUS);

	glDetachShader(handle, vertex_shader_handle);

	glDetachShader(handle, fragment_shader_handle);
}

void ShaderProgram::use() {
	glUseProgram(handle);
}

GLuint ShaderProgram::get_handle() {
	return handle;
}