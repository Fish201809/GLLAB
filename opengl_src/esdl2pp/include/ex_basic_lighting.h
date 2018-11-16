#pragma once

#include "exobject.h"
#include "common.h"

class ShaderProgram;

class EXBasicLighting : public EXObject
{
public:
	virtual void Init() override;


	virtual void RenderGL(std::shared_ptr<ProjectionCamera> camera) override;


	virtual void RenderGUI() override;

private:
	void GenerateShader();

private:
	std::shared_ptr<ShaderProgram> phone_shader_ = nullptr;
	std::shared_ptr<ShaderProgram> gourand_shader_ = nullptr;

	bool phone_gourand_flag = true;

	std::shared_ptr<ShaderProgram> light_shader_ = nullptr;

	GLuint cube_vao_;
	GLuint light_vao_;

	glm::vec3 light_color_= glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 cube_color_ = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 cube_position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 light_position_ = glm::vec3(1.15f, 1.150f, -1.4f);

	GLfloat uambient_strength = 0.0f;
	GLfloat udiffuse_strength = 0.3f;
	GLfloat uspecular_strength = 0.6f;
	GLint ushininess = 200;
};

/**
 * 在观察空间计算光照
 ------ vertex shader ---------------
 #version 450 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vCoord;
layout(location = 3) in vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectMatrix;
uniform vec3 uLightPosition;


out vec3 fPosition;	//传递到观察空间的片元坐标
out vec3 fColor;	//片段颜色
out vec3 fCoord;
out vec3 fNormal; //法线矩阵变换后的法线
out vec3 fLightPosition; //传递到观察空间的光源坐标


void main(){
	gl_Position = uProjectMatrix * uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f);

	fPosition = vec3(uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f));
	fColor = vColor;
	fCoord = vCoord;
	fNormal = mat3(transpose(inverse(uViewMatrix * uModelMatrix))) * vNormal;
	fLightPosition = vec3(uViewMatrix * vec4(uLightPosition, 1.0f));
}
 ------ fragment shader ---------------

 #version 450 core

in vec3 fPosition;	//传递到观察空间的片元坐标
in vec3 fColor;
in vec3 fCoord;
in vec3 fNormal; //法线矩阵变换后的法线
in vec3 fLightPosition; //传递到观察空间的光源坐标

uniform vec3 uLightColor;

out vec4 Color;


void main(){
	vec3 normal = normalize(fNormal);
	vec3 light_direction = normalize(fLightPosition - fPosition);
	vec3 reflect_direction = normalize(reflect(-light_direction, normal));
	vec3 camera_direction = normalize(-fPosition);

	//计算环境光
	float ambient_strength = 0.1f;
	vec3 ambient_influence = ambient_strength * uLightColor;

	//计算漫反射光
	float diffuse_strength = 0.5f;
	vec3 diffuse_influence = max(dot(normal, light_direction), 0.0f) * diffuse_strength * uLightColor;

	//计算镜面反射
	float specular_strength = 0.8f;
	vec3 specular_influence = pow(max(dot(reflect_direction , camera_direction), 0.0f), 256) * specular_strength * uLightColor;
	Color = vec4(ambient_influence + diffuse_influence + specular_influence, 1.0f) * vec4(fColor, 1.0f);
	//Color = vec4(ambient_influence,1.0f) * vec4(fColor, 1.0f);	//环境光效果
	//Color = vec4(diffuse_influence, 1.0f) * vec4(fColor, 1.0f);	//漫反射效果
	//Color = vec4(specular_influence,1.0f) * vec4(fColor, 1.0f);	//镜面反射效果
}
 */