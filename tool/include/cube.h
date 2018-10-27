#pragma once


#include "shaderprogram.h"

class Cube
{
public:
	virtual void display();

	virtual void init();

	GLuint ebo_;
	GLuint vao_;
	GLuint vbo_;
	GLuint texture_;
	std::shared_ptr<ShaderProgram> program_;
};
