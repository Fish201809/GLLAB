﻿
#include "tool.h"


enum VBOTYPE
{
	CHESS, NUMVBO
};

const int VERTEX_NUM = 11;

static GLfloat vbo_chess_vertex[VERTEX_NUM * VERTEX_NUM][3] = {
};

static GLuint ebo_chess[(VERTEX_NUM - 1) * (VERTEX_NUM - 1)][6] = {
};

static GLfloat vbo_chess_color[VERTEX_NUM * VERTEX_NUM][3] = {
};

GLuint VAO, EBO;
GLuint VBO[NUMVBO] = {};
GLuint fbo;
GLuint buffer;
ShaderProgram *shader_program = nullptr;



class ExampleTemplateTest : public ExampleTemplate
{
	void init() {
		//设置随机数
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_real_distribution<GLfloat> dis(0.0f, 1.0f);
		auto dice = std::bind(dis, engine);

		//准备顶点数据
		for (int i = 0; i < VERTEX_NUM; i++) {
			for (int j = 0; j < VERTEX_NUM; j++) {
				vbo_chess_vertex[i * VERTEX_NUM + j][0] = static_cast<GLfloat>(i) - VERTEX_NUM / 2;
				vbo_chess_vertex[i * VERTEX_NUM + j][1] = static_cast<GLfloat>(j) - VERTEX_NUM / 2;
				vbo_chess_vertex[i * VERTEX_NUM + j][2] = 0.0f;

				GLfloat r = dice();
				GLfloat g = dice();
				GLfloat b = dice();
				vbo_chess_color[i * VERTEX_NUM + j][0] = r;
				vbo_chess_color[i * VERTEX_NUM + j][1] = g;
				vbo_chess_color[i * VERTEX_NUM + j][2] = b;
			}
		}
		shader_program = new ShaderProgram;
		shader_program->attach_vertex_shader("basic.vert");
		shader_program->attach_fragment_shader("basic.frag");
		shader_program->link();
		shader_program->use();

		for (int i = 0; i < VERTEX_NUM - 1; i++) {
			for (int j = 0; j < VERTEX_NUM - 1; j++) {
				ebo_chess[i * (VERTEX_NUM - 1) + j][0] = i * VERTEX_NUM + j;
				ebo_chess[i * (VERTEX_NUM - 1) + j][1] = i * VERTEX_NUM + j + 1;
				ebo_chess[i * (VERTEX_NUM - 1) + j][2] = (i + 1) * VERTEX_NUM + j;

				ebo_chess[i * (VERTEX_NUM - 1) + j][3] = i * VERTEX_NUM + j + 1;
				ebo_chess[i * (VERTEX_NUM - 1) + j][4] = (i + 1) * VERTEX_NUM + j;
				ebo_chess[i * (VERTEX_NUM - 1) + j][5] = (i + 1) * VERTEX_NUM + j + 1;
			}
		}

		glCreateVertexArrays(1, &VAO);
		glCreateBuffers(NUMVBO, VBO);
		glCreateBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[CHESS]);

		glNamedBufferStorage(VBO[CHESS], sizeof(vbo_chess_vertex) + sizeof(vbo_chess_color), 0, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(VBO[CHESS], 0, sizeof(vbo_chess_vertex), vbo_chess_vertex);
		glNamedBufferSubData(VBO[CHESS], sizeof(vbo_chess_vertex), sizeof(vbo_chess_color), vbo_chess_color);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vbo_chess_vertex));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glNamedBufferStorage(EBO, sizeof(ebo_chess), ebo_chess, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void display() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(15.0f);*/
		glm::mat4 ortho_matrix = glm::ortho(-(float)(VERTEX_NUM - 1) / 2, (float)(VERTEX_NUM - 1) / 2, -(float)(VERTEX_NUM - 1) / 2, (float)(VERTEX_NUM - 1) / 2);
		static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		shader_program->use();
		shader_program->set_uniform_mat4("project", camera_->get_matrix());

		//shader_program->set_uniform_mat4("project", orcho_camera.get_matrix());

		GLfloat time = (float)glfwGetTime();


		glm::mat4 rotate_matrix = glm::mat4(1.0f);
		//rotate_matrix = glm::rotate(rotate_matrix, glm::radians(time) * 10.0f, glm::vec3(0.0, 0.0, 1.0));

		//glm::mat4 translate_matrix_go = glm::mat4(1.0f);
		//translate_matrix_go = glm::translate(translate_matrix_go, glm::vec3( static_cast<GLfloat> (-VERTEX_NUM / 2), static_cast<GLfloat> (-VERTEX_NUM / 2), 0.0f));

		//glm::mat4 translate_matrix_back = glm::mat4(1.0f);
		//translate_matrix_back = glm::translate(translate_matrix_back, glm::vec3(static_cast<GLfloat> (VERTEX_NUM  / 2), static_cast<GLfloat> (VERTEX_NUM/ 2), 0.0f));

		/*glm::mat4 look_at_matrix = glm::mat4(1.0f);
		look_at_matrix = glm::lookAt(glm::vec3(VERTEX_NUM /2, VERTEX_NUM / 2, -1.0f), glm::vec3(VERTEX_NUM / 2, VERTEX_NUM / 2,0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

		//glm::mat4 model_matrix = orcho_camera.get_ortho_matrix() * /*translate_matrix_back * */rotate_matrix/* * translate_matrix_go*/;
		//trans = glm::translate(trans, glm::vec3(static_cast<GLfloat> (VERTEX_NUM / 2), static_cast<GLfloat> (VERTEX_NUM / 2), 0.0f));

		glm::mat4 model_matrix = glm::mat4(1.0f);
		shader_program->set_uniform_mat4("model_matrix", model_matrix);

		glClearBufferfv(GL_COLOR, 0, black);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, (VERTEX_NUM - 1) * (VERTEX_NUM - 1) * 6, GL_UNSIGNED_INT, 0);
	}

};


ExampleTemplateTest test;



int main(int agrc, char *argv[]) {
	test.run();

	return 0;
}