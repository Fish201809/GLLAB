#pragma once

#include "tool.h"


class Cube
{
public:
	Cube() {
		
	}
	virtual void display(){
	
		program_->use();
		glm::mat4 vp_matrix = camera_->get_matrix();
		program_->set_uniform_mat4("vp_matrix", vp_matrix);
		glm::mat4 model_matrix = glm::mat4(1.0f);
		glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));
		glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), (float)(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
		program_->set_uniform_mat4("model_matrix", rotate_matrix * translate_matrix);
		glBindVertexArray(vao_);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}


	virtual void init() {

		static const GLfloat cube_data[][3]{
			{-5.0f, -5.0f, 5.0f},
			{5.0f, -5.0f, 5.0f},
			{5.0f, 5.0f, 5.0f},
			{-5.0f, 5.0f, 5.0f},
			{-5.0f, -5.0f, -5.0f},
			{5.0f, -5.0f, -5.0f},
			{5.0f, 5.0f, -5.0f},
			{-5.0f, 5.0f, -5.0f}
		};

		static GLuint cube_ebo_data[][3]{
			{0, 1, 2},
			{2, 1, 3},
			{4, 5, 6},
			{4, 6, 7},
			{0, 5, 1},
			{0, 4, 5},
			{3, 2, 6},
			{3, 6, 7},
			{1, 5, 2},
			{2, 5, 6},
			{4, 0, 3},
			{4, 3, 7},
		};

		program_ = std::make_shared<ShaderProgram>();
		program_->attach_vertex_shader("basic.vert");
		program_->attach_fragment_shader("basic.frag");
		program_->link();
		program_->use();
		glCreateVertexArrays(1, &vao_);
		glCreateBuffers(1, &vbo_);
		glCreateBuffers(1, &ebo_);
		glNamedBufferStorage(vbo_, sizeof(cube_data), nullptr, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo_, 0, sizeof(cube_data), cube_data);
		glNamedBufferStorage(ebo_, sizeof(cube_ebo_data), cube_ebo_data, GL_DYNAMIC_STORAGE_BIT);

		glBindVertexArray(vao_);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	GLuint ebo_;
	GLuint vao_;
	GLuint vbo_;
	std::shared_ptr<ShaderProgram> program_;
};

