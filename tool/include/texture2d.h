#pragma once

#include <gl/gl3w.h>
#include <string>
#include <vector>

class Texture2D
{
public:
	Texture2D(std::vector<GLfloat> &data, int width, int height, int channel);
	Texture2D(int width, int height, int format);
	Texture2D(std::string name);

	GLuint get_handle() { return handle_; }
	void bind() const;
private:
	GLuint handle_;
	int width, height;
	int nrChannels;
private:
	void generate(const std::string &path);
	void generate(int width, int height, int format);
};

