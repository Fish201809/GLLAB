#include "tool.h"


/**
 * 冯氏光照模型(Phong Lighting Model)
 * 环境光照(Ambient Lighting)
 * 漫反射光照(Diffuse Lighting)
 * 镜面光照(Specular Lighting)
 */

struct Materix
{
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular_color;
	float shininess;
};

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
		glm::mat4 translate_position = glm::translate(glm::mat4(1.0f), position_);
		light_source_geo->set_model_matrix(translate_position);
		light_source_geo->Render(ShaderLoader::GetShaderProgram("tbasic"));
	}
	void Update(float time) {
		position_.y =  sin(glfwGetTime())* 16;
		position_.x = sin(glfwGetTime()) * 5;
		position_.z = sin(glfwGetTime()) * 16;


		color_.x = sin(glfwGetTime() * 2.0f);
		color_.y = sin(glfwGetTime() * 0.7f);
		color_.z = sin(glfwGetTime() * 1.3f);

		

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
		glm::mat4 translate_position = glm::translate(glm::mat4(1.0f), position_);
		toy_geo->set_model_matrix(translate_position);
		toy_geo->Render(shader_program);
	}
	void Update(float time) {
	
	}
	glm::vec3 Color() const { return color_; }
	void Color(glm::vec3 val) { color_ = val; }
private:
	shared_ptr<Cube> toy_geo = nullptr;
	glm::vec3 color_ = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 position_ = glm::vec3(-15.0f, 0.0f, 0.0f);
};


class EXMoveLight : public ExampleTemplate
{
public:
	EXMoveLight() {
		//floor_ = std::make_shared<Plane>(std::make_unique<Texture2D>(FileSystem::getPath("image/chess.jpg")));
		toy_ = std::make_shared<Toy>();
		light_source_ = std::make_shared<LightSource>();
	}
	virtual void render() override {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glm::mat4 model_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(15.0f, 1.0f, 15.0f));
		/*	floor_->set_model_matrix(model_matrix);
			floor_->Render(ShaderLoader::GetShaderProgram("tbasic"));*/
		light_source_->Render();
		glm::vec3 lColor = light_source_->Color();
		glm::vec3 lPosition = light_source_->Position();
		glm::vec3 lCameraPosition = gcamera->World_position();

		glm::vec3 diffuseColor = lColor * glm::vec3(0.5f); // 降低影响
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

		ShaderLoader::GetShaderProgram("light_material2").use();
		//ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uLightColor", lColor.x, lColor.y, lColor.z);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uLightPosition", lPosition.x, lPosition.y, lPosition.z);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uCameraPosition", lCameraPosition.x, lCameraPosition.y, lCameraPosition.z);
		
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uMaterial.ambient_color", 1.0f, 0.5f, 0.31f);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uMaterial.diffuse_color", 1.0f, 0.5f, 0.31f);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uMaterial.specular_color", 0.5f, 0.5f, 0.5f);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_1f("uMaterial.shininess", 32.0f);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uLightMaterial.ambient", ambientColor);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uLightMaterial.diffuse", diffuseColor);
		ShaderLoader::GetShaderProgram("light_material2").set_uniform_vec3("uLightMaterial.specular", 1.0f, 1.0f, 1.0f);
	
		toy_->Render(ShaderLoader::GetShaderProgram("light_material2"));
	}

	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	virtual void update(float time) override {
		light_source_->Update(time);
		toy_->Update(time);
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