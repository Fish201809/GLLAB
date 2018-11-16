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
		std::cout << info << std::endl;
	}
}

ShaderProgram::ShaderProgram() {
	handle = glCreateProgram();
}

ShaderProgram::ShaderProgram(const std::string &vert_path, const std::string &frag_path, bool link_flag) {
	handle = glCreateProgram();
	attach_vertex_shader_file(vert_path);
	attach_fragment_shader_file(frag_path);
	if (link_flag) {
		this->link();
	}
}

void ShaderProgram::attach_vertex_shader_file(const std::string &path) {
	Native native(path);



	// load shader source
	std::string core = native.read().c_str();

	attach_vertex_shader(core);
}

void ShaderProgram::attach_fragment_shader_file(const std::string &path) {
	Native native(path);


	// load shader source
	std::string core = native.read().c_str();
	attach_fragment_shader(core);
}

void ShaderProgram::attach_tess_control_shader_file(const std::string &path) {
	Native native(path);



	// load shader source
	std::string core = native.read().c_str();
	attach_tess_control_shader(core);
}

void ShaderProgram::attach_tess_evaluation_shader_file(const std::string &path) {
	Native native(path);

	

	// load shader source
	std::string core = native.read().c_str();
	const char* data = core.c_str();
	attach_tess_evaluation_shader(core);
}

void ShaderProgram::attach_vertex_shader(const std::string &path) {

	// allocate shader in opengl
	vertex_shader_handle = glCreateShader(GL_VERTEX_SHADER);

	const char* data = path.c_str();
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
		std::cout << info << std::endl;
	}
	glAttachShader(handle, vertex_shader_handle);
}

void ShaderProgram::attach_fragment_shader(const std::string &path) {


	// allocate shader in opengl
	fragment_shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
	const char* data = path.c_str();
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
		std::cout << info << std::endl;
	}
	glAttachShader(handle, fragment_shader_handle);
}

void ShaderProgram::attach_tess_control_shader(const std::string &path) {

	// allocate shader in opengl
	tess_control_handle_ = glCreateShader(GL_TESS_CONTROL_SHADER);

	// load shader source
	const char* data = path.c_str();
	glShaderSource(tess_control_handle_, 1, &data, nullptr);

	// compile shader source
	glCompileShader(tess_control_handle_);

	// check compiliation result
	GLint status;
	glGetShaderiv(tess_control_handle_, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv(tess_control_handle_, GL_INFO_LOG_LENGTH, &loglen);

		std::vector<char> infolog(loglen);
		glGetShaderInfoLog(tess_control_handle_, loglen, nullptr, infolog.data());

		std::string info = std::string() + "Failed to compiler tesc shader:\n" + infolog.data();
		std::cout << info << std::endl;
	}
	glAttachShader(handle, tess_control_handle_);
}

void ShaderProgram::attach_tess_evaluation_shader(const std::string &path) {
	// allocate shader in opengl
	tess_evaluation_handle_ = glCreateShader(GL_TESS_EVALUATION_SHADER);

	const char* data = path.c_str();
	glShaderSource(tess_evaluation_handle_, 1, &data, nullptr);

	// compile shader source
	glCompileShader(tess_evaluation_handle_);

	// check compiliation result
	GLint status;
	glGetShaderiv(tess_evaluation_handle_, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv(tess_evaluation_handle_, GL_INFO_LOG_LENGTH, &loglen);

		std::vector<char> infolog(loglen);
		glGetShaderInfoLog(tess_evaluation_handle_, loglen, nullptr, infolog.data());

		std::string info = std::string() + "Failed to compiler tese shader:\n" + infolog.data();
		std::cout << info << std::endl;
	}
	glAttachShader(handle, tess_evaluation_handle_);
}

bool ShaderProgram::set_uniform_mat4(const std::string &name, const glm::mat4 &mat) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniformMatrix4fv(location_id, 1, GL_FALSE, &mat[0][0]);
	return true;
}

bool ShaderProgram::set_uniform_1i(const std::string &name, GLint texture_id) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniform1i(location_id, texture_id);
	return true;
}


bool ShaderProgram::set_uniform_1ui(const std::string &name, GLuint texture_id) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniform1ui(location_id, texture_id);
	return true;
}

bool ShaderProgram::set_uniform_vec3(const std::string &name, float x, float y, float z) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniform3f(location_id, x, y, z);
	return true;
}

bool ShaderProgram::set_uniform_vec3(const std::string &name, glm::vec3 value) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniform3f(location_id, value.x, value.y, value.z);
	return true;
}

bool ShaderProgram::set_uniform_vec4(const std::string &name, float x, float y, float z, float w) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniform4f(location_id, x, y, z, w);
	return true;
}

bool ShaderProgram::set_uniform_1f(const std::string &name, GLfloat value) {
	GLint location_id = glGetUniformLocation(handle, name.c_str());
	glUniform1f(location_id, value);
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