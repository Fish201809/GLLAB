#include "Plane.h"
#include "tool.h"

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
		glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Plane::init() {
	static const GLfloat cube_data[][3]{
			{-5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, 5.0f},
			{-5.0f, 0.0f, -5.0f},
			{5.0f, 0.0f, 5.0f},
			{-5.0f, 0.0f, 5.0f}
	};

	program_ = std::make_shared<ShaderProgram>();
	program_->attach_vertex_shader("plane.vert");
	program_->attach_fragment_shader("plane.frag");
	program_->link();
	program_->use();
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glNamedBufferStorage(vbo_, sizeof(cube_data), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_, 0, sizeof(cube_data), cube_data);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
