#pragma once

#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include "shaderprogram.h"
#include "OrthoCamera.h"
#include "ProjectionCamera.h"


class Plane
{
public:
	Plane() {

	}
	virtual void display();
	virtual void init();
	GLuint vao_;
	GLuint vbo_;
	GLuint texture_;
	std::shared_ptr<ShaderProgram> program_;
};