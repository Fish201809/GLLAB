#include "tool.h"
#include "framebufferobject.h"


class ObjectCube
{
public:
	ObjectCube(){
		std::vector<GLfloat> light_data = {
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f
		};
		cube_geo_ = std::make_shared<Cube>(std::make_unique<Texture2D>(light_data, 2, 2, 4));
	}
	void Render(ShaderProgram &shaderprogram) {
		shaderprogram.use();
		cube_geo_->set_model_matrix(glm::translate(glm::mat4(1.0f), position_));
		cube_geo_->Render(shaderprogram);
	}
	
	glm::vec3 Position() const { return position_; }
	void Position(glm::vec3 val) { position_ = val; }
private:
	shared_ptr<Cube> cube_geo_ = nullptr;
	glm::vec3 position_ = glm::vec3(0.0f, 5.0f, 0.0f);
};

std::vector<shared_ptr<ObjectCube>> cubes;


/**
 * 移动高亮显示效果
 */
class EXMoveLight : public ExampleTemplate
{
public:
	EXMoveLight() {
		floor_ = std::make_shared<Plane>(std::make_unique<Texture2D>(FileSystem::getPath("image/chess.jpg")));
		cubes.push_back(std::make_shared<ObjectCube>());
		cubes.push_back(std::make_shared<ObjectCube>());

		frame_ = std::make_unique<FrameBufferObject>();
		frame_->AttachTetxureColor(WIN_WIDTH, WIN_HEIGHT);
		frame_->AttachRenderBuffer(WIN_WIDTH, WIN_HEIGHT);
		frame_->Check();
	}
	virtual void display() override {
		frame_->bind();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cubes[1]->Position(glm::vec3(10.0f, 15.0f, 10.0f));
		for (GLuint i = 0; i < cubes.size(); ++i) {
			ShaderLoader::GetShaderProgram("drawindex").use();
			ShaderLoader::GetShaderProgram("drawindex").set_uniform_1ui("uIndex", i);
			cubes[i]->Render(ShaderLoader::GetShaderProgram("drawindex"));
		}

		static GLuint data_texture;
		glReadPixels(xpos, ypos, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, (void*)&data_texture);
		std::cout << data_texture << std::endl;
		frame_->unbind();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (GLuint i = 0; i < cubes.size(); ++i) {
			ShaderLoader::GetShaderProgram("ucolor").use();
			if (i == data_texture) {
				ShaderLoader::GetShaderProgram("ucolor").set_uniform_vec4("uColor", 0.3f, 0.4f, 0.5f, 1.0f);
			}
			else {
				ShaderLoader::GetShaderProgram("ucolor").set_uniform_vec4("uColor", 0.1f, 0.8f, 0.2f, 1.0f);
			}
			cubes[i]->Render(ShaderLoader::GetShaderProgram("ucolor"));
		}
	}

	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

public:
	shared_ptr<ObjectCube> object_cube_ = nullptr;
	shared_ptr<ObjectCube> object_cube2_ = nullptr;
	shared_ptr<Plane> floor_ = nullptr;
	std::unique_ptr<FrameBufferObject> frame_;
};


int main(int agrc, char *argv[]) {
	EXMoveLight basic_light;
	basic_light.run();

	return 0;
}