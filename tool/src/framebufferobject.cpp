#include "framebufferobject.h"
#include "texture2d.h"

static float frame_vbo[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
};

FrameBufferObject::FrameBufferObject() {

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(frame_vbo), frame_vbo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glGenFramebuffers(1, &fbo_);
	
}

void FrameBufferObject::AttachTetxureColor(int width, int height){
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	texture_ = std::make_unique<Texture2D>(width, height, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT);
	//设置纹理附件
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_->get_handle(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::AttachRenderBuffer(int width, int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	glGenRenderbuffers(1, &rbo_);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//深度和模板附件渲染缓冲对象附件
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::Check() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
}

void FrameBufferObject::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::Render() {
	glBindVertexArray(vao_);
	glDisable(GL_DEPTH_TEST);
	texture_->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);

}
