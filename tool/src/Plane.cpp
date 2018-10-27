#include "Plane.h"
#include "tool.h"
#include "loadimage.h"


extern std::shared_ptr<Camera> camera_;

void Plane::display() {
		
		program_->use();
		glm::mat4 vp_matrix = camera_->get_matrix();
		program_->set_uniform_mat4("vp_matrix", vp_matrix);
		glm::mat4 model_matrix = glm::mat4(1.0f);
		glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 10.0f));
		/*	glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));
			glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), (float)(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));*/
		program_->set_uniform_mat4("model_matrix", scale_matrix);
		glBindVertexArray(vao_);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_);
		glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Plane::init() {
	static const GLfloat cube_data[][3] = {
			{-5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, 5.0f},
			{-5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, 5.0f},
			{-5.0f, 0.0f, 5.0f}
	};
	static const GLfloat plane_cord[][2] = {
		{0.0f, 0.0f}, 
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
	};

	program_ = std::make_shared<ShaderProgram>();
	program_->attach_vertex_shader(FileSystem::getPath("shaders/plane.vert"));
	program_->attach_fragment_shader(FileSystem::getPath("shaders/plane.frag"));
	program_->link();
	program_->use();
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glNamedBufferStorage(vbo_, sizeof(cube_data) + sizeof(plane_cord), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_, 0, sizeof(cube_data), cube_data);
	glNamedBufferSubData(vbo_, sizeof(cube_data), sizeof(plane_cord), plane_cord);


	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)sizeof(cube_data));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	int width, height, channels;

	
	GLubyte *data = load_image("image/chess.jpg", width, height, channels);
	if (data == nullptr) {
		std::cout << "loag image failed" << std::endl;
	}
	else {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		free(data);
	}
}
