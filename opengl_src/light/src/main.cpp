#include "tool.h"


/**
 * 冯氏光照模型(Phong Lighting Model)
 * 环境光照(Ambient Lighting)
 * 漫反射光照(Diffuse Lighting)
 * 镜面光照(Specular Lighting)
 */

class LightSource
{
public:
	LightSource() {
		std::vector<GLfloat> light_data = {
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f,
			1.0f, 1.0f, 1.0f,1.0f
		};
		light_source_geo = std::make_shared<Cube>(std::make_unique<Texture2D>(light_data, 2, 2, 4));
	}
	void Render() {
		light_source_geo->set_model_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(25.0f, 0.0f, 0.0f)));
		light_source_geo->Render(ShaderLoader::GetShaderProgram("tbasic"));
	}
	glm::vec3 Color() const { return color_; }
	void Color(glm::vec3 val) { color_ = val; }
	glm::vec3 Position() const { return position_; }
	void Position(glm::vec3 val) { position_ = val; }
private:
	shared_ptr<Cube> light_source_geo = nullptr;
	glm::vec3 color_ = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 position_ = glm::vec3(25.0f, 0.0f, 0.0f);
};



class Toy
{
public:
	Toy() {
		std::vector<GLfloat> light_data = {
			1.0f, 0.5f, 0.31f,1.0f,
			1.0f, 0.5f, 0.31f,1.0f,
			1.0f, 0.5f, 0.31f,1.0f,
			1.0f, 0.5f, 0.31f,1.0f
		};
		toy_geo = std::make_shared<Cube>(glm::vec3(1.0f, 0.5f, 0.31f), std::make_unique<Texture2D>(light_data, 2, 2, 4));
	}
	void Render(ShaderProgram &shader_program) {
		toy_geo->set_model_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 0.0f, 0.0f)));
		toy_geo->Render(shader_program);
	}
	glm::vec3 Color() const { return color_; }
	void Color(glm::vec3 val) { color_ = val; }
private:
	shared_ptr<Cube> toy_geo = nullptr;
	glm::vec3 color_ = glm::vec3(1.0f, 0.5f, 0.31f);
};


class EXMoveLight : public ExampleTemplate
{
public:
	EXMoveLight() {
		//floor_ = std::make_shared<Plane>(std::make_unique<Texture2D>(FileSystem::getPath("image/chess.jpg")));
		toy_ = std::make_shared<Toy>();
		light_source_ = std::make_shared<LightSource>();
	}
	virtual void display() override {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glm::mat4 model_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(15.0f, 1.0f, 15.0f));
		/*floor_->set_model_matrix(model_matrix);
		floor_->Render(ShaderLoader::GetShaderProgram("tbasic"));*/
		light_source_->Render();
		glm::vec3 lColor = light_source_->Color();
		glm::vec3 lPosition = light_source_->Position();
		glm::vec3 lCameraPosition = gcamera->World_position();
		ShaderLoader::GetShaderProgram("light_view").use();
		ShaderLoader::GetShaderProgram("light_view").set_uniform_vec3("uLightColor", lColor.x, lColor.y, lColor.z);
		ShaderLoader::GetShaderProgram("light_view").set_uniform_vec3("uLightPosition", lPosition.x, lPosition.y, lPosition.z);
		ShaderLoader::GetShaderProgram("light_view").set_uniform_vec3("uCameraPosition", lCameraPosition.x, lCameraPosition.y, lCameraPosition.z);
		toy_->Render(ShaderLoader::GetShaderProgram("light_view"));
	}

	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
public:
	//shared_ptr<Plane> floor_ = nullptr;
	shared_ptr<LightSource> light_source_ = nullptr;
	shared_ptr<Toy> toy_ = nullptr;
};


int main(int agrc, char *argv[]) {
	EXMoveLight basic_light;
	basic_light.run();
	return 0;
}