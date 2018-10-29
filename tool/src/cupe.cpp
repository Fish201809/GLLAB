#include "cube.h"
#include "tool.h"
#include "filesystem.h"

#include <stb_image.h>

extern std::shared_ptr<Camera> camera_;

static const GLfloat cube_vbo_vertex[]{
	 -5.0f, -5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
		 5.0f, -5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
		 5.0f,  5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
		 5.0f,  5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
		-5.0f,  5.0f, -5.0f,  0.0f,  0.0f, -1.0f,
		-5.0f, -5.0f, -5.0f,  0.0f,  0.0f, -1.0f,

		-5.0f, -5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
		 5.0f, -5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
		 5.0f,  5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
		 5.0f,  5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
		-5.0f,  5.0f,  5.0f,  0.0f,  0.0f,  1.0f,
		-5.0f, -5.0f,  5.0f,  0.0f,  0.0f,  1.0f,

		-5.0f,  5.0f,  5.0f, -1.0f,  0.0f,  0.0f,
		-5.0f,  5.0f, -5.0f, -1.0f,  0.0f,  0.0f,
		-5.0f, -5.0f, -5.0f, -1.0f,  0.0f,  0.0f,
		-5.0f, -5.0f, -5.0f, -1.0f,  0.0f,  0.0f,
		-5.0f, -5.0f,  5.0f, -1.0f,  0.0f,  0.0f,
		-5.0f,  5.0f,  5.0f, -1.0f,  0.0f,  0.0f,

		 5.0f,  5.0f,  5.0f,  1.0f,  0.0f,  0.0f,
		 5.0f,  5.0f, -5.0f,  1.0f,  0.0f,  0.0f,
		 5.0f, -5.0f, -5.0f,  1.0f,  0.0f,  0.0f,
		 5.0f, -5.0f, -5.0f,  1.0f,  0.0f,  0.0f,
		 5.0f, -5.0f,  5.0f,  1.0f,  0.0f,  0.0f,
		 5.0f,  5.0f,  5.0f,  1.0f,  0.0f,  0.0f,

		-5.0f, -5.0f, -5.0f,  0.0f, -1.0f,  0.0f,
		 5.0f, -5.0f, -5.0f,  0.0f, -1.0f,  0.0f,
		 5.0f, -5.0f,  5.0f,  0.0f, -1.0f,  0.0f,
		 5.0f, -5.0f,  5.0f,  0.0f, -1.0f,  0.0f,
		-5.0f, -5.0f,  5.0f,  0.0f, -1.0f,  0.0f,
		-5.0f, -5.0f, -5.0f,  0.0f, -1.0f,  0.0f,

		-5.0f,  5.0f, -5.0f,  0.0f,  1.0f,  0.0f,
		 5.0f,  5.0f, -5.0f,  0.0f,  1.0f,  0.0f,
		 5.0f,  5.0f,  5.0f,  0.0f,  1.0f,  0.0f,
		 5.0f,  5.0f,  5.0f,  0.0f,  1.0f,  0.0f,
		-5.0f,  5.0f,  5.0f,  0.0f,  1.0f,  0.0f,
		-5.0f,  5.0f, -5.0f,  0.0f,  1.0f,  0.0f
};

static GLfloat cube_vbo_color[][3]{
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},

	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},

	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},

	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},

	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},

	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f},
	{1.0f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
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

Cube::Cube(glm::vec3 color, std::unique_ptr<Texture2D> texture) {
	texture_ = std::move(texture);
	for (auto item : cube_vbo_color) {
		item[0] = color.x;
		item[1] = color.y;
		item[2] = color.z;
	}
	Init();
}


Cube::Cube(std::unique_ptr<Texture2D> texture) {
	texture_ = std::move(texture);
	Init();
}


void Cube::set_model_matrix(glm::mat4 model_matrix) {
	model_matrix_ = model_matrix;
}


void Cube::Render(ShaderProgram &shader_program) {

	glm::mat4 vp_matrix = camera_->get_matrix();
	shader_program.use();
	shader_program.set_uniform_mat4("vp_matrix", vp_matrix);
	shader_program.set_uniform_mat4("model_matrix", model_matrix_);

	glBindVertexArray(vao_);
	texture_->bind();
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Cube::Init() {
	
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	//glCreateBuffers(1, &ebo_);
	glNamedBufferStorage(vbo_, sizeof(cube_vbo_vertex) + sizeof(cube_vbo_color) + sizeof(cube_vbo_texture), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(vbo_, 0, sizeof(cube_vbo_vertex), cube_vbo_vertex);
	glNamedBufferSubData(vbo_, sizeof(cube_vbo_vertex), sizeof(cube_vbo_color), cube_vbo_color);
	glNamedBufferSubData(vbo_, sizeof(cube_vbo_vertex) + sizeof(cube_vbo_color), sizeof(cube_vbo_texture), cube_vbo_texture);

	//glNamedBufferStorage(ebo_, sizeof(cube_ebo_data), cube_ebo_data, GL_DYNAMIC_STORAGE_BIT);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)sizeof(cube_vbo_vertex));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)( sizeof(cube_vbo_vertex) + sizeof(cube_vbo_color) ));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}







