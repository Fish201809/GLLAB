#include "tool.h"
#include <stb_image.h>

class LightCube : public Cube
{

public:
	virtual void InitTexture() override {
		static const GLfloat text_data[] = {
			1.0f, 0.0f, 0.0f,1.0f,
			0.0f, 0.0f, 0.0f,0.0f,
			1.0f, 0.0f, 0.0f,1.0f,
			0.0f, 0.0f, 0.0f,1.0f,
		};
		int width, height, nrChannels;
		unsigned char *data = stbi_load(FileSystem::getPath("image/guaishao.jpg").c_str(), &width, &height, &nrChannels, 0);
		//unsigned char *data = load_image("image/guaishao.jpg", width, height, nrChannels);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, texture_->get_handle());
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, text_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
};

class MyCube : public Cube
{

public:
	virtual void InitTexture() override {

		static const GLubyte text_data[] = {
			0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,
			0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0XFF,
			0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,
			0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0XFF,
			0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,
			0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0XFF,
			0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,
			0X00,0xFF, 0X00,0xFF, 0X00,0xFF, 0X00,0XFF
		};
		int width, height, nrChannels;
		//unsigned char *data = stbi_load(FileSystem::getPath("image/guaishao.jpg").c_str(), &width, &height, &nrChannels, 0);
		//unsigned char *data = load_image("image/guaishao.jpg", width, height, nrChannels);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, texture_->get_handle());
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_BLUE, GL_UNSIGNED_BYTE, text_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		//stbi_image_free(data);
	}
};

class EXFrameBufferRenderAttach : public ExampleTemplate
{
public:
	EXFrameBufferRenderAttach(std::string ex_name) :ExampleTemplate(ex_name) {
		plane_ = std::make_shared<Plane>();
		cube_ = std::make_shared<MyCube>();
		cube2_ = std::make_shared<LightCube>();
	}
	virtual ~EXFrameBufferRenderAttach() {
	}
	virtual void render() override {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane_->Render(TODO);

		/*glm::mat4 model_matrix = glm::mat4(1.0f);
		glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 0.0f));*/
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 15.0f, 0.0f));
		glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), (float)(glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
		glm::mat4 model_matrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 15.0f, 20.0f));

		cube_->Render(model_matrix * rotate_matrix);
		cube2_->Render(model_matrix2);

	}

	virtual void init() override {
		plane_->Init();
		cube_->Init();
		cube2_->Init();

	}
	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
private:
	std::shared_ptr<Plane> plane_;
	std::shared_ptr<Cube> cube_;
	std::shared_ptr<Cube> cube2_;

	GLuint vao_;
	GLuint vbo_;
	GLuint fbo_;
	shared_ptr<ShaderProgram> frame_program_ = nullptr;
};



int main(int agrc, char *argv[]) {
	EXFrameBufferRenderAttach e("Off-screen rendering - Texture");
	//EXFrameBufferTextureAttach e2("Off-screen rendering - Texture");
	e.run();

	return 0;
}