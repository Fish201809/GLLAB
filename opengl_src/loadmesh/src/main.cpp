//#include "tool.h"
//#include "model.h"
//
//
//class EXFrameBufferTextureAttach : public ExampleTemplate
//{
//public:
//	EXFrameBufferTextureAttach(std::string ex_name) :ExampleTemplate(ex_name) {
//		plane_ = std::make_shared<Plane>();
//		cube_ = std::make_shared<Cube>();
//		model_ = std::make_shared<Model>(FileSystem::getPath("model/nanosuit/nanosuit.obj"));
//
//	}
//	virtual ~EXFrameBufferTextureAttach() {
//	}
//	virtual void render() override {
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glEnable(GL_DEPTH_TEST);
//
//
//		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 15.0f, 0.0f));
//		
//		model_->setMatrix(model_matrix);
//		model_->render(ShaderLoader::GetShaderProgram("test"));
//		plane_->Render(TODO);
//	}
//
//	virtual void init() override {
//		plane_->Init();
//		cube_->Init();
//	}
//	virtual void set_state() override {
//		glEnable(GL_DEPTH_TEST);
//	}
//private:
//	std::shared_ptr<Plane> plane_;
//	std::shared_ptr<Cube> cube_;
//	std::shared_ptr<Model> model_ = nullptr;
//};
//
//
//
//int main(int agrc, char *argv[]) {
//	EXFrameBufferTextureAttach e2("Off-screen rendering - Texture");
//	e2.run();
//
//	return 0;
//}
