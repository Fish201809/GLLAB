#pragma once



class ShaderProgram;
class Texture2D;
class Camera;

class Plane
{
public:
	explicit Plane(std::unique_ptr<Texture2D> texture);
	virtual void Render(ShaderProgram &shader_program, std::shared_ptr<Camera> camera);
	void set_model_matrix(glm::mat4 model_matrix);
private:
	virtual void Init();

	GLuint vao_;
	GLuint vbo_;

	std::unique_ptr<Texture2D> texture_ = nullptr;
	glm::mat4 model_matrix_ = glm::mat4(1.0f);
	glm::mat4 vp_matrix_ = glm::mat4(1.0f);

	std::shared_ptr<ShaderProgram> program_;
};