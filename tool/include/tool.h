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
#include "filesystem.h"
#include "plane.h"
#include "cube.h"
#include "loadimage.h"
#include "shader_manager.h"


#pragma warning( disable : 4244 )


extern std::shared_ptr<Camera> camera_;

using namespace std;


constexpr int WIN_WIDTH = 800;
constexpr int WIN_HEIGHT = 600;

class ExampleTemplate
{
public:
	ExampleTemplate();
	ExampleTemplate(std::string ex_name);
	virtual ~ExampleTemplate();
	GLFWwindow *window = nullptr;
	void setting(std::string ex_name);

public:
	virtual void set_state() = 0;
	virtual void init() = 0;
	virtual void display() = 0;
	virtual void run();
	void process_key(GLFWwindow *window);
	float frame_rate = 0.0f;
	float elapse_time = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};




