#pragma once

//曲面细分
#include <gl/gl3w.h>
#include <memory>

class ShaderProgram;

class TesslationShader
{
public:
	TesslationShader();
	void Init();
	void Render();
private:
	std::shared_ptr<ShaderProgram> shader_program_;
	GLuint vao_;
	GLuint vbo_;

private:
	GLuint patch_vertex_num_ = 4;	//设置单个面片的顶点数目
};


/**
 * 细分着色器
 * 细分控制着色器 -- 获得顶点的 uv 或者 xyz 重心坐标
 * 细分计算着色器 -- 生成顶点的 位置 坐标
 */