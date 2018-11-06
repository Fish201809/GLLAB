#pragma once

#include "common.h"

class Texture2D
{
public:
	/**
	 * 根据vector中的数据生成纹理，内部纹理使用rgba格式， channel需为3或者4通道
	 */
	Texture2D(std::vector<GLfloat> &data, int width, int height, int channel);
	/**
	 * width 纹理宽度
	 * height 纹理高度
	 * internal_format 纹理存储的内部格式
	 * format 输入的纹理数据格式
	 * type 输入像素数据的类型
	 */
	Texture2D(int width, int height, int internal_format, int format, int type);
	/**
	 * 从图片文件生成纹理
	 */
	Texture2D(const std::string &file_name);

	GLuint get_handle() { return handle_; }
	void bind() const;
private:
	GLuint handle_;
	int width, height;
	int nrChannels;
};

