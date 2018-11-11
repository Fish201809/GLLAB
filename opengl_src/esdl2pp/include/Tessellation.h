#pragma once

#include <gl/gl3w.h>
#include <memory>
#include "common.h"

class ShaderProgram;

//细分例子构建器
class Tessellation
{
public:
	Tessellation();
	virtual ~Tessellation();
	void Init();
	void SetUniform();
	void Render();
	void GenerateGui();
	void BindVAO();
	void SwitchVBO(GLuint num);
	std::shared_ptr<ShaderProgram> GenerateShader();

	std::string Primitype() const { return primitype; }
	void Primitype(std::string val) { primitype = val; }
	std::string Subdivision_level() const { return subdivision_level; }
	void Subdivision_level(std::string val) { subdivision_level = val; }
	std::string Face_toward() const { return face_toward; }
	void Face_toward(std::string val) { face_toward = val; }
	GLuint Patch_vertices() const { return patch_vertices_; }
	void Patch_vertices(GLuint val);
private:
	std::shared_ptr<ShaderProgram> current_shader_program = nullptr;
	GLuint vao_;
	GLuint vbo_;


	GLfloat outer_0 = 1.0f;
	GLfloat outer_1 = 1.0f;
	GLfloat outer_2 = 1.0f;
	GLfloat outer_3 = 1.0f;

	GLfloat inter_0 = 1.0f;
	GLfloat inter_1 = 1.0f;

	std::string primitype = "triangles";
	std::string subdivision_level = "equal_spacing";
	std::string face_toward = "ccw";

	GLuint patch_vertices_ = 3;
};
