#include "tool.h"

class EXFrameBufferRenderAttach : public ExampleTemplate
{
public:
	EXFrameBufferRenderAttach(std::string ex_name):ExampleTemplate(ex_name) {
		plane_ = std::make_shared<Plane>();
		cube_ = std::make_shared<Cube>();
	}
	virtual ~EXFrameBufferRenderAttach() {
		glDeleteFramebuffers(1, &fbo_);
	}
	virtual void display() override {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		plane_->display();
		cube_->display();

		glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		frame_program_->use();
		glBindVertexArray(vao_);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, texture_);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	virtual void init() override {
		plane_->init();
		cube_->init();
		

		frame_program_ = std::make_shared<ShaderProgram>();
		frame_program_->attach_vertex_shader(FileSystem::getPath("shaders/frame.vert"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_lnversion.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_grayscale.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_grayscale_widget.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_kernel.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_blur.frag"));
		frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_edge_detection.frag"));
		frame_program_->link();

		static float frame_vbo[] = {
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
		};

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
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

		glGenTextures(1, &texture_);
		glBindTexture(GL_TEXTURE_2D, texture_);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		//设置纹理附件
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);

		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		//深度和模板附件渲染缓冲对象附件
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
	}
private:
	std::shared_ptr<Plane> plane_;
	std::shared_ptr<Cube> cube_;

	GLuint vao_;
	GLuint vbo_;
	GLuint fbo_;
	GLuint texture_;
	shared_ptr<ShaderProgram> frame_program_ = nullptr;
};

class EXFrameBufferTextureAttach : public ExampleTemplate
{
public:
	EXFrameBufferTextureAttach(std::string ex_name) :ExampleTemplate(ex_name) {
		plane_ = std::make_shared<Plane>();
		cube_ = std::make_shared<Cube>();
	}
	virtual ~EXFrameBufferTextureAttach() {
		glDeleteFramebuffers(1, &fbo_);
	}
	virtual void display() override {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		plane_->display();
		cube_->display();

		glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		frame_program_->use();
		glBindVertexArray(vao_);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, texture_);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	virtual void init() override {
		plane_->init();
		cube_->init();

		frame_program_ = std::make_shared<ShaderProgram>();
		frame_program_->attach_vertex_shader(FileSystem::getPath("shaders/frame.vert"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_lnversion.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_grayscale.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_grayscale_widget.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_kernel.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_blur.frag"));
		frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_edge_detection.frag"));
		frame_program_->link();

		static float frame_vbo[] = {
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,

			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
		};

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
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

		glGenTextures(1, &texture_);
		glBindTexture(GL_TEXTURE_2D, texture_);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		//设置纹理颜色附件
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);


		glGenTextures(1, &texture_depth_stencil_);
		glBindTexture(GL_TEXTURE_2D, texture_depth_stencil_);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
		);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture_depth_stencil_, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
	}
private:
	std::shared_ptr<Plane> plane_;
	std::shared_ptr<Cube> cube_;

	GLuint vao_;
	GLuint vbo_;
	GLuint fbo_;
	GLuint texture_;
	GLuint texture_depth_stencil_;
	shared_ptr<ShaderProgram> frame_program_ = nullptr;
};



int main(int agrc, char *argv[]) {
//	EXFrameBufferRenderAttach e("Off-screen rendering - Texture");
	EXFrameBufferTextureAttach e2("Off-screen rendering - Texture");
	e2.run();

	return 0;
}