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

#include "plane.h"


#pragma warning( disable : 4244 )

using namespace std;




class ExampleTemplate
{
public:
	ExampleTemplate();
	
	GLFWwindow *window = nullptr;
	void setting();

public:
	virtual void init();
	virtual void display();
	virtual void run();
	void process_key(GLFWwindow *window);
	float frame_rate = 0.0f;
	float elapse_time = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	std::shared_ptr<Plane> plane;
};


extern std::shared_ptr<Camera> camera_;



