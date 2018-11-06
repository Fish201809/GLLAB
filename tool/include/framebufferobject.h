#pragma once

#include "common.h"

class Texture2D;

class FrameBufferObject
{
public:

	FrameBufferObject();
	void AttachTetxureColor(int width, int height);
	void AttachRenderBuffer(int width, int height);
	void Check();
	void bind();
	void unbind();
	void Render();
private:
	GLuint fbo_;
	GLuint vao_;
	GLuint vbo_;
	GLuint rbo_;
	std::unique_ptr<Texture2D> texture_ = nullptr;
};
