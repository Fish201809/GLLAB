#include "tool.h"
#include "model.h"


class EXFrameBufferTextureAttach : public ExampleTemplate
{
public:
	EXFrameBufferTextureAttach(std::string ex_name) :ExampleTemplate(ex_name) {
		plane_ = std::make_shared<Plane>();
		cube_ = std::make_shared<Cube>();

		model_ = std::make_shared<Model>(FileSystem::getPath("model/nanosuit/nanosuit.obj"));

	}
	virtual ~EXFrameBufferTextureAttach() {
	}
	virtual void display() override {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		//plane_->display();
		frame_program_->use();
		frame_program_->set_uniform_mat4("vp_matrix", camera_->get_matrix());
		frame_program_->set_uniform_mat4("model_matrix", glm::mat4(1.0f));
	

	
		//cube_->display();
		
		model_->render(*frame_program_);
		plane_->display();
	}

	virtual void init() override {
		plane_->init();
		cube_->init();

		frame_program_ = std::make_shared<ShaderProgram>();
		frame_program_->attach_vertex_shader(FileSystem::getPath("shaders/test.vert"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_lnversion.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_grayscale.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_grayscale_widget.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_kernel.frag"));
		//frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/frame_blur.frag"));
		frame_program_->attach_fragment_shader(FileSystem::getPath("shaders/test.frag"));
		frame_program_->link();
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
	
	std::shared_ptr<Model> model_ = nullptr;
};



int main(int agrc, char *argv[]) {
	//	EXFrameBufferRenderAttach e("Off-screen rendering - Texture");
	EXFrameBufferTextureAttach e2("Off-screen rendering - Texture");
	e2.run();

	return 0;
}
