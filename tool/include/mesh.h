#pragma once

#include <gl/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex
{
	// 坐标
	glm::vec3 position;
	// 法线
	glm::vec3 normal;
	// 纹理坐标(只载入了一个)
	glm::vec2 cord;
	// 切线
	glm::vec3 tangent;
	// 双切线
	glm::vec3 bitangent;
};

struct Texture
{
	//纹理 ID
	GLuint id;
	/**
	 *      纹理贴图
	 * 	 1. diffuse maps
		 2. specular maps
		 3. normal maps
		 4. height maps
	 */
	string type;
	//纹理路径
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices, const vector<Texture> &textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		init();
	}

	void draw(ShaderProgram &shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i); 
			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); 
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);
			shader.set_uniform_1i((name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

private:
	unsigned int VBO, EBO;


	void init() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 结构体内存布局连续性
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// 1用于颜色跳过
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, cord));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);
	
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		glEnableVertexAttribArray(4);
		
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
		glEnableVertexAttribArray(5);

		glBindVertexArray(0);
	}
};
