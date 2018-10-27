
#include "tool.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static const GLfloat cube_vbo_vertex[][3]{
	{-5.0f, -5.0f, 5.0f},
	{5.0f, -5.0f,5.0f},
	{5.0f, 5.0f, 5.0f},
	{-5.0f, 5.0f,5.0f},
	{-5.0f, -5.0f, -5.0f},
	{5.0f, -5.0f, -5.0f},
	{5.0f, 5.0f, -5.0f},
	{-5.0f, 5.0f, -5.0f}
};


static const GLfloat cube_vbo_color[][3]{
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f}
};
static const GLfloat cube_vbo_texture[][2]{
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f},
	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},
	{0.0f, 1.0f}
};

static GLubyte chess_texture[][8] = {
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00},
	{0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff},
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00},
	{0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff},
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00},
	{0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff},
	{0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00},
	{0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff},
};

static GLubyte color_texture[4 * 3]{
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	255, 255, 0,
};


static GLuint cube_ebo_data[][3]{
	{0, 1, 2},
	{0, 2, 3},
	{4, 6, 5},
	{4, 7, 6},
	{0, 5, 1},
	{0, 4, 5},
	{3, 2, 6},
	{3, 6, 7},
	{1, 5, 2},
	{2, 5, 6},
	{4, 0, 3},
	{4, 3, 7}
};


class ElementSphere: public ExampleTemplate
{
public:

	virtual void display() override {
	
		program_->use();
		glm::mat4 vp_matrix = camera_->get_matrix();
		program_->set_uniform_mat4("vp_matrix", vp_matrix);
		glm::mat4 model_matrix = glm::mat4(1.0f);
		glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 0.0f));
		glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), (float)(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
		program_->set_uniform_mat4("model_matrix", /*rotate_matrix * */translate_matrix);
		glBindVertexArray(vao_);
		glBindTexture(GL_TEXTURE_2D, texture_);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		__super::display();
	}


	virtual void init() override {
		
		program_ = std::make_shared<ShaderProgram>();
		program_->attach_vertex_shader("basic.vert");
		program_->attach_fragment_shader("basic.frag");
		program_->link();
		program_->use();
		glCreateVertexArrays(1, &vao_);
		glCreateBuffers(1, &vbo_);
		glCreateBuffers(1, &ebo_);
		glNamedBufferStorage(vbo_, sizeof(cube_vbo_vertex) + sizeof(cube_vbo_color) + sizeof(cube_vbo_texture), nullptr, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo_, 0, sizeof(cube_vbo_vertex), cube_vbo_vertex);
		glNamedBufferSubData(vbo_, sizeof(cube_vbo_vertex), sizeof(cube_vbo_color), cube_vbo_color);
		glNamedBufferSubData(vbo_, sizeof(cube_vbo_vertex) + sizeof(cube_vbo_texture), sizeof(cube_vbo_texture), cube_vbo_texture);


		glNamedBufferStorage(ebo_, sizeof(cube_ebo_data), cube_ebo_data, GL_DYNAMIC_STORAGE_BIT);

		glBindVertexArray(vao_);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)sizeof(cube_vbo_vertex));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(cube_vbo_vertex)+ sizeof(cube_vbo_texture)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//设置纹理
		//int width, height, nrChannels;
		//unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glGenTextures(1, &texture_);
		//glBindTexture(GL_TEXTURE_2D, texture_);
		////glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_INT, color_texture);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glGenerateMipmap(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glGenTextures(1, &texture_);
		glBindTexture(GL_TEXTURE_2D, texture_);
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// 加载并生成纹理
		int width, height, nrChannels;
		/*	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				std::cout << "Failed to load texture" << std::endl;
			}
			stbi_image_free(data);*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2,2, 0, GL_RGB, GL_UNSIGNED_BYTE, color_texture);
		glGenerateMipmap(GL_TEXTURE_2D);

		/*	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);*/
		__super::init();
	}
	GLuint ebo_;
	GLuint vao_;
	GLuint vbo_;
	GLuint texture_;
	std::shared_ptr<ShaderProgram> program_;
};


int main(int agrc, char *argv[]) {
	ElementSphere e;
	e.run();

	return 0;
}











