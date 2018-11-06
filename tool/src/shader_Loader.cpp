//#include "resource_manager.h"
//
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <stb_image.h>
//#include "shaderprogram.h"
//
//// Instantiate static variables
//std::map<std::string, Texture2D>      ResourceManager::Textures;
//std::map<std::string, std::unique_ptr<ShaderProgram>>  ResourceManager::Shaders;
//
//
//ShaderProgram ResourceManager::LoadShaderProgram(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
//	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
//	return Shaders[name];
//}
//
//void ResourceManager::LoadShaderProgram(std::unique_ptr<ShaderProgram> shader_program, const std::string &name) {
//	Shaders[name] = shader_program;
//	ShaderProgram[name].res
//}
//
//ShaderProgram ResourceManager::GetShaderProgram(std::string name) {
//	return Shaders[name];
//}
//
//Texture2D ResourceManager::LoadTexture(const std::string &path, GLboolean alpha, std::string name) {
//	Textures[name] = loadTextureFromFile(path, alpha);
//	return Textures[name];
//}
//
//Texture2D ResourceManager::GetTexture(std::string name) {
//	return Textures[name];
//}
//
//void ResourceManager::Clear() {
//	// (Properly) delete all shaders	
//	for (auto iter : Shaders)
//		glDeleteProgram(iter.second.get_handle());
//	// (Properly) delete all textures
//	for (auto iter : Textures)
//		glDeleteTextures(1, &iter.second.id);
//}
//
//ShaderProgram ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile) {
//	// 1. Retrieve the vertex/fragment source code from filePath
//	std::string vertexCode;
//	std::string fragmentCode;
//	std::string geometryCode;
//	try {
//		// Open files
//		std::ifstream vertexShaderFile(vShaderFile);
//		std::ifstream fragmentShaderFile(fShaderFile);
//		std::stringstream vShaderStream, fShaderStream;
//		// Read file's buffer contents into streams
//		vShaderStream << vertexShaderFile.rdbuf();
//		fShaderStream << fragmentShaderFile.rdbuf();
//		// close file handlers
//		vertexShaderFile.close();
//		fragmentShaderFile.close();
//		// Convert stream into string
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//		// If geometry shader path is present, also load a geometry shader
//		if (gShaderFile != nullptr) {
//			std::ifstream geometryShaderFile(gShaderFile);
//			std::stringstream gShaderStream;
//			gShaderStream << geometryShaderFile.rdbuf();
//			geometryShaderFile.close();
//			geometryCode = gShaderStream.str();
//		}
//	}
//	catch (std::exception e) {
//		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
//	}
//	const GLchar *vShaderCode = vertexCode.c_str();
//	const GLchar *fShaderCode = fragmentCode.c_str();
//	const GLchar *gShaderCode = geometryCode.c_str();
//	// 2. Now create shader object from source code
//	ShaderProgram shader;
//	shader.attach_vertex_shader(vShaderCode);
//	shader.attach_fragment_shader(fShaderCode);
//	shader.link();
//	//shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
//	return shader;
//}
//
//
//Texture2D ResourceManager::loadTextureFromFile(const std::string &path, GLboolean alpha) {
//	// Create Texture object
//	Texture2D texture;
//	if (alpha) {
//		texture.internal_format = GL_RGBA;
//		texture.image_format = GL_RGBA;
//	}
//	// Load image
//	int width, height, channels;
//	unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
//	// Now generate texture
//	texture.generate(width, height, image);
//	stbi_image_free(image);
//	return texture;
//}
//

#include "shader_Loader.h"
#include "texture2d.h"
#include "shaderprogram.h"



std::map<std::string, std::unique_ptr<ShaderProgram>>  ShaderLoader::Shaders;

void ShaderLoader::LoadShaderProgram(std::unique_ptr<ShaderProgram> shader_program, const std::string &name) {
	Shaders[name] = std::move(shader_program);
}

ShaderProgram& ShaderLoader::GetShaderProgram(std::string name) {
	return *Shaders[name];
}
