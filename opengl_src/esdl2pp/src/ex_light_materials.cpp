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
	if (phone_gourand_flag) {
		phone_shader_->use();
		phone_shader_->set_uniform_mat4("umodel_matrix", glm::mat4(1.0f));
		phone_shader_->set_uniform_mat4("uview_matrix", camera->get_view_matrix());
		phone_shader_->set_uniform_mat4("uproject_matrix", camera->get_project_matrix());
		phone_shader_->set_uniform_vec3("uobject_color", cube_color_);
		phone_shader_->set_uniform_vec3("ulight_color", light_color_);
		phone_shader_->set_uniform_vec3("ucamera_position", camera->World_position());
		phone_shader_->set_uniform_vec3("ulight_position", light_position_);
		//PHONE光强分配
		phone_shader_->set_uniform_1f("uambient_strength", uambient_strength);
		phone_shader_->set_uniform_1f("udiffuse_strength", udiffuse_strength);
		phone_shader_->set_uniform_1f("uspecular_strength", uspecular_strength);
		phone_shader_->set_uniform_1i("ushininess", ushininess);
	}
	else {
		gourand_shader_->use();
		gourand_shader_->set_uniform_mat4("umodel_matrix", glm::mat4(1.0f));
		gourand_shader_->set_uniform_mat4("uview_matrix", camera->get_view_matrix());
		gourand_shader_->set_uniform_mat4("uproject_matrix", camera->get_project_matrix());
		gourand_shader_->set_uniform_vec3("uobject_color", cube_color_);
		gourand_shader_->set_uniform_vec3("ulight_color", light_color_);
		gourand_shader_->set_uniform_vec3("ucamera_position", camera->World_position());
		gourand_shader_->set_uniform_vec3("ulight_position", light_position_);
		//PHONE光强分配
		gourand_shader_->set_uniform_1f("uambient_strength", uambient_strength);
		gourand_shader_->set_uniform_1f("udiffuse_strength", udiffuse_strength);
		gourand_shader_->set_uniform_1f("uspecular_strength", uspecular_strength);
		gourand_shader_->set_uniform_1i("ushininess", ushininess);
	}



	glBindVertexArray(cube_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	light_shader_->use();
	light_shader_->set_uniform_mat4("umodel_matrix", glm::translate(glm::mat4(1.0f), light_position_) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)));
	light_shader_->set_uniform_mat4("uview_matrix", camera->get_view_matrix());
	light_shader_->set_uniform_mat4("uproject_matrix", camera->get_project_matrix());

	glBindVertexArray(light_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void  EXLightMaterials::RenderGUI() {
	ImGui::Begin("EXBasicLighting");
	{
		ImGui::DragFloat("uambient_strength", &uambient_strength, 0.01f);
		ImGui::DragFloat("udiffuse_strength", &udiffuse_strength, 0.01f);
		ImGui::DragFloat("uspecular_strength", &uspecular_strength, 0.01f);

		ImGui::DragInt("ushininess", &ushininess, 1.0f);
		ImGui::DragFloat("x", &light_position_[0], 0.05f);
		ImGui::DragFloat("y", &light_position_[1], 0.05f);
		ImGui::DragFloat("z", &light_position_[2], 0.05f);

		ImGui::Checkbox("Phone", &phone_gourand_flag);
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
		"uniform vec3 uobject_color;\n"
		"uniform vec3 ulight_color;\n"
		"uniform vec3 ulight_position;\n"
		"uniform vec3 ucamera_position;\n"

		"uniform float uambient_strength;\n"
		"uniform float udiffuse_strength;\n"
		"uniform float uspecular_strength;\n"
		"uniform int ushininess;\n"

		"void main() {\n"
		"//环境光\n"
		"vec3 ambient = uambient_strength * ulight_color;\n"
		"vec3 light_direction = ulight_position - fPosition;\n"
		"vec3 viewDir = normalize(ucamera_position - fPosition);\n"
		"vec3 normal = normalize(fNormal);\n"
		"light_direction = normalize(light_direction);\n"
		"//漫反射\n"
		"float diff = max(dot(normal, light_direction), 0.0);\n"
		"vec3 diffuse = udiffuse_strength * diff * ulight_color;\n"
		"//镜面反射\n"

		"vec3 reflectDir = reflect(-light_direction, normal);\n"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), ushininess);\n"
		"vec3 specular = uspecular_strength * spec * ulight_color;\n"
		"vec3 result = (ambient + diffuse + specular) * uobject_color;\n"
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

	//gourand 着色模型
	std::string gourand_vertex_shader = "#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"layout(location = 3) in vec3 vNormal;\n"
		"uniform mat4 umodel_matrix;\n"
		"uniform mat4 uview_matrix;\n"
		"uniform mat4 uproject_matrix;\n"
		"uniform vec3 ulight_position;\n"
		"uniform vec3 ulight_color;\n"
		"uniform vec3 uobject_color;\n"

		"uniform float uambient_strength;\n"
		"uniform float udiffuse_strength;\n"
		"uniform float uspecular_strength;\n"
		"uniform int ushininess;\n"


		"out vec3 fColor;	//片段颜色\n"
		"void main() {\n"
		"	vec4 view_position = uview_matrix * umodel_matrix * vec4(vPosition, 1.0f);\n"
		"	gl_Position = uproject_matrix * view_position;\n"
		"	vec3 normal = normalize(mat3(transpose(inverse(uview_matrix * umodel_matrix))) * vNormal);\n"
		"	vec3 light_position = vec3(uview_matrix * vec4(ulight_position, 1.0f));\n"
		"	vec3 light_direction = normalize(light_position - view_position.xyz);\n"
		"	//计算环境光\n"
		"	vec3 ambient_influence = uambient_strength * uobject_color * ulight_color;\n"
		"	//计算漫反射\n"
		"	vec3 diffuse_influence = dot(light_direction, normal) * uobject_color * ulight_color * udiffuse_strength;\n"
		"	//计算镜面反射\n"
		"	vec3 specular_influence = pow(max(dot(normalize(reflect(-light_direction, normal)), normalize(-view_position.xyz)), 0.0f), ushininess) * uobject_color * ulight_color;\n"
		"	fColor = ambient_influence + diffuse_influence + uspecular_strength * specular_influence;\n"
		"}\n";
	std::string gourand_fragment_shader = "#version 450 core\n"
		"in vec3 fColor;\n"
		"out vec4 Color;\n"
		"void main() {\n"
		"	Color = vec4(fColor, 1.0f);\n"
		"}\n";
	gourand_shader_ = std::make_shared<ShaderProgram>();
	gourand_shader_->attach_vertex_shader(gourand_vertex_shader);
	gourand_shader_->attach_fragment_shader(gourand_fragment_shader);
	gourand_shader_->link();
}
