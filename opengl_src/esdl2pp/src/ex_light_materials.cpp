#include "ex_light_materials.h"
#include "shaderprogram.h"
#include <vector>
#include "ProjectionCamera.h"


void EXLightMaterials::Init() {
	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cube_vao_);
	glBindVertexArray(cube_vao_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glGenVertexArrays(1, &light_vao_);
	glBindVertexArray(light_vao_);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	GenerateShader();
}

void  EXLightMaterials::RenderGL(std::shared_ptr<ProjectionCamera> camera) {
	
	phone_shader_->use();
	phone_shader_->set_uniform_mat4("umodel_matrix", glm::mat4(1.0f));
	phone_shader_->set_uniform_mat4("uview_matrix", camera->get_view_matrix());
	phone_shader_->set_uniform_mat4("uproject_matrix", camera->get_project_matrix());
	phone_shader_->set_uniform_vec3("ucamera_position", camera->World_position());

	//物体材质
	phone_shader_->set_uniform_vec3("materials.ambient", material_.ambient);
	phone_shader_->set_uniform_vec3("materials.diffuse", material_.diffuse);
	phone_shader_->set_uniform_vec3("materials.specular", material_.specular);
	phone_shader_->set_uniform_1f("materials.shininess", material_.shininess);

	//光分量和位置
	phone_shader_->set_uniform_vec3("light_attr.ambient", light_attr_.ambient);
	phone_shader_->set_uniform_vec3("light_attr.diffuse", light_attr_.diffuse);
	phone_shader_->set_uniform_vec3("light_attr.specular", light_attr_.specular);
	phone_shader_->set_uniform_vec3("light_attr.position", light_attr_.position);

	glBindVertexArray(cube_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	light_shader_->use();
	light_shader_->set_uniform_mat4("umodel_matrix", glm::translate(glm::mat4(1.0f), light_attr_.position) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)));
	light_shader_->set_uniform_mat4("uview_matrix", camera->get_view_matrix());
	light_shader_->set_uniform_mat4("uproject_matrix", camera->get_project_matrix());

	glBindVertexArray(light_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void  EXLightMaterials::RenderGUI() {
	ImGui::Begin("EXLightMaterials");
	{
		ImGui::DragFloat3("material ambient", &material_.ambient[0], 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat3("material diffuse", &material_.diffuse[0], 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat3("material specular", &material_.specular[0], 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("shininess", &material_.shininess, 0.1f);

		ImGui::DragFloat3("light ambient", &light_attr_.ambient[0], 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat3("light diffuse", &light_attr_.diffuse[0], 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat3("light specular", &light_attr_.specular[0], 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat("x", &light_attr_.position[0], 0.01f);
		ImGui::DragFloat("y", &light_attr_.position[1], 0.01f);
		ImGui::DragFloat("z", &light_attr_.position[2], 0.01f);
	}
	ImGui::End();
}

void  EXLightMaterials::GenerateShader() {
	//Phone 着色模型
	std::string phone_vertex_shader =
		"#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"layout(location = 3) in vec3 vNormal;\n"
		"uniform mat4 umodel_matrix;\n"
		"uniform mat4 uview_matrix;\n"
		"uniform mat4 uproject_matrix;\n"
		"out vec3 fNormal;\n"
		"out vec3 fPosition;\n"
		"void main(){\n"
		"	gl_Position = uproject_matrix * uview_matrix * umodel_matrix * vec4(vPosition, 1.0f);\n"
		"	fPosition = vec3(umodel_matrix * vec4(vPosition, 1.0));\n"
		"   fNormal = mat3(transpose(inverse(umodel_matrix))) * vNormal;\n"
		"};\n";

	std::string phone_fragment_shader =
		"#version 450 core\n"
		"//冯氏着色(Phong Shading)\n"
		"in vec3 fNormal;\n"
		"in vec3 fPosition;\n"
		"out vec4 Color;\n"

		"struct Materials{\n"
		"	vec3 ambient;\n"
		"	vec3 diffuse;\n"
		"	vec3 specular;\n"
		"	float shininess;\n"
		"};\n"

		"struct LightAttr{\n"
		"	vec3 position;\n"
		"	vec3 ambient;\n"
		"	vec3 diffuse;\n"
		"	vec3 specular;\n"
		"};\n"

		"uniform LightAttr light_attr;\n"
		"uniform Materials materials;\n"
		"uniform vec3 ucamera_position;\n"

		"void main() {\n"
		"//环境光\n"
		"vec3 ambient = materials.ambient * light_attr.ambient;\n"

		"vec3 light_direction = light_attr.position - fPosition;\n"
		"vec3 viewDir = normalize(ucamera_position - fPosition);\n"
		"vec3 normal = normalize(fNormal);\n"
		"light_direction = normalize(light_direction);\n"
		"//漫反射\n"
		"float diff = max(dot(normal, light_direction), 0.0);\n"
		"vec3 diffuse = diff * light_attr.diffuse * materials.diffuse;\n"
		"//镜面反射\n"

		"vec3 reflectDir = reflect(-light_direction, normal);\n"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), materials.shininess);\n"
		"vec3 specular = spec * materials.specular * light_attr.specular;\n"
		"vec3 result = ambient + diffuse + specular;\n"
		"Color = vec4(result, 1.0f);\n"
		"};\n";
	phone_shader_ = std::make_shared<ShaderProgram>();
	phone_shader_->attach_vertex_shader(phone_vertex_shader);
	phone_shader_->attach_fragment_shader(phone_fragment_shader);
	phone_shader_->link();

	std::string light_vertex_shader =
		"#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"uniform mat4 umodel_matrix;\n"
		"uniform mat4 uview_matrix;\n"
		"uniform mat4 uproject_matrix;\n"
		"void main(){\n"
		"	gl_Position = uproject_matrix * uview_matrix * umodel_matrix * vec4(vPosition, 1.0f);\n"
		"};\n";

	std::string light_fragment_shader =
		"#version 450 core\n"
		"out vec4 Color;\n"
		"void main(){\n"
		"	Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n";
	light_shader_ = std::make_shared<ShaderProgram>();
	light_shader_->attach_vertex_shader(light_vertex_shader);
	light_shader_->attach_fragment_shader(light_fragment_shader);
	light_shader_->link();
}
