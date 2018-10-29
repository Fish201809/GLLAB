#pragma once

#include <map>
#include <memory>
#include <string>

#include "texture2d.h"
#include "shaderprogram.h"



class ShaderLoader
{
public:
	// Resource storage
	static std::map<std::string, std::unique_ptr<ShaderProgram>>    Shaders;
	//static std::map<std::string, std::unique_ptr<Texture2D>> Textures;
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static void LoadShaderProgram(std::unique_ptr<ShaderProgram> shader_program, const std::string &name);
	
	// Retrieves a stored sader
	static ShaderProgram&  GetShaderProgram(std::string name);
	//// Loads (and generates) a texture from file
	//static Texture2D LoadTexture(const std::string &path, GLboolean alpha, std::string name);
	//// Retrieves a stored texture
	//static Texture2D GetTexture(std::string name);
	//// Properly de-allocates all loaded resources
	//static void      Clear();
private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ShaderLoader() {}
	//// Loads and generates a shader from file
	//static ShaderProgram    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	//// Loads a single texture from file
	//static Texture2D loadTextureFromFile(const std::string &path, GLboolean alpha);
};