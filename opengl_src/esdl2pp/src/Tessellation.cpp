#include "Tessellation.h"
#include "shaderprogram.h"
#include "filesystem.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


Tessellation::Tessellation() {

}

Tessellation::~Tessellation() {

}

void Tessellation::Init() {
	BindVAO();
	current_shader_program = GenerateShader();
}


void Tessellation::SetUniform() {
	current_shader_program->use();

	current_shader_program->set_uniform_1f("outer_0", outer_0);
	current_shader_program->set_uniform_1f("outer_1", outer_1);
	current_shader_program->set_uniform_1f("outer_2", outer_2);
	current_shader_program->set_uniform_1f("outer_3", outer_3);

	current_shader_program->set_uniform_1f("inter_0", inter_0);
	current_shader_program->set_uniform_1f("inter_1", inter_1);
}

void Tessellation::Render() {
	SetUniform();

	glBindVertexArray(vao_);
	glDrawArrays(GL_PATCHES, 0, 8);
}

void Tessellation::GenerateGui() {
	{
		ImGui::Begin("Tessellation example");
		{
			ImGui::InputFloat("outer_0", &outer_0, 1.0f, 10.0f);
			ImGui::InputFloat("outer_1", &outer_1, 1.0f, 10.0f);
			ImGui::InputFloat("outer_2", &outer_2, 1.0f, 10.0f);
			ImGui::InputFloat("outer_3", &outer_3, 1.0f, 10.0f);
			ImGui::InputFloat("inter_0", &inter_0, 1.0f, 10.0f);
			ImGui::InputFloat("inter_1", &inter_1, 1.0f, 10.0f);
		}
		{
			const char* items[] = { "triangles",  "isolines", "quads" };
			static int item_current = 0;
			if (ImGui::Combo("primitype", &item_current, items, IM_ARRAYSIZE(items))) {
				if (item_current == 0) {
					Primitype("triangles");
					current_shader_program = GenerateShader();
				}
				else if (item_current == 1) {
					Primitype("isolines");
					current_shader_program = GenerateShader();
				}
				else if (item_current == 2) {
					Primitype("quads");
					current_shader_program = GenerateShader();
				}
			}
		}

		{
			const char* items[] = { "equal_spacing",  "fractional_even_spacing", "fractional_odd_spacing" };
			static int item_current = 0;
			if (ImGui::Combo("subdivision_level", &item_current, items, IM_ARRAYSIZE(items))) {
				if (item_current == 0) {
					Subdivision_level("equal_spacing");
					current_shader_program = GenerateShader();
				}
				else if (item_current == 1) {
					Subdivision_level("fractional_even_spacing");
					current_shader_program = GenerateShader();
				}
				else if (item_current == 2) {
					Subdivision_level("fractional_odd_spacing");
					current_shader_program = GenerateShader();
				}
			}
		}

		{
			const char* items[] = { "ccw",  "cw"};
			static int item_current = 0;
			if (ImGui::Combo("face_toward", &item_current, items, IM_ARRAYSIZE(items))) {
				if (item_current == 0) {
					Face_toward("ccw");
					current_shader_program = GenerateShader();
				}
				else if (item_current == 1) {
					Face_toward("cw");
					current_shader_program = GenerateShader();
				}
			}
		}

		{
			const char* items[] = { "3",  "4" };
			static int item_current = 0;
			if (ImGui::Combo("switch_vbo", &item_current, items, IM_ARRAYSIZE(items))) {
				if (item_current == 0) {
					SwitchVBO(3);
					current_shader_program = GenerateShader();
				}
				else if (item_current == 1) {
					SwitchVBO(4);
					current_shader_program = GenerateShader();
				}
			}
		}

		ImGui::End();
	}
}

void Tessellation::BindVAO() {
	glCreateVertexArrays(1, &vao_);
	glCreateBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	SwitchVBO(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	Patch_vertices(3);
	glEnableVertexAttribArray(0);
}


void Tessellation::SwitchVBO(GLuint num) {
	if (num == 3) {
		Patch_vertices(3);
		static GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	else if (num == 4) {
		Patch_vertices(4);
		static GLfloat vertices[] = {
			-0.5f, -0.5f,0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
}

std::shared_ptr<ShaderProgram> Tessellation::GenerateShader() {

	static std::string version_info = "#version 450 core\n";

	std::string vertex_shader = "#version 450 core\n"
		"layout(location = 0) in vec3 vPosition;\n"
		"void main() {\n"
		"gl_Position = vec4(vPosition, 1.0f);\n"
		"}\n";

	std::string fragment_shader = "#version 450 core\n"
		"out vec4 Color;\n"
		"void main() {\n"
		"Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n";

	std::string tesc_layout = "ERROR";
	if (patch_vertices_ == 3) {
		tesc_layout = "layout(vertices = 3) out;\n";
	}
	else if(patch_vertices_ == 4){
		tesc_layout = "layout(vertices = 4) out;\n";
	}
	
	std::string tesc_shader = version_info + tesc_layout +
		"uniform float outer_0;\n"
		"uniform float outer_1;\n"
		"uniform float outer_2;\n"
		"uniform float outer_3;\n"
		"uniform float inter_0;\n"
	    "uniform float inter_1;\n"

		"void main(void) {\n"
		"if (gl_InvocationID == 0) {\n"
			"gl_TessLevelOuter[0] = outer_0;\n"
			"gl_TessLevelOuter[1] = outer_1;\n"
			"gl_TessLevelOuter[2] = outer_2;\n"
			"gl_TessLevelOuter[3] = outer_3;\n"
			"gl_TessLevelInner[0] = inter_0;\n"
			"gl_TessLevelInner[1] = inter_1;\n"
		"}\n"
		"gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"
		"}\n";

	
	std::string tese_layout = "layout(" + this->Primitype() + "," +  this->Subdivision_level() + "," + this->Face_toward() + ") in; \n";

	std::string tese_shader = "";

	if (Patch_vertices() == 4) {
		tese_shader = version_info + tese_layout +
			"void main(void) {\n"
			"	float u = gl_TessCoord.x;\n"
			"	float omu = 1 - u;\n"
			"	float v = gl_TessCoord.y;\n"
			"	float omv = 1 - v;\n"
			"	gl_Position = omu * omv * gl_in[0].gl_Position +\n"
			"		u * omv * gl_in[1].gl_Position +\n"
			"		u * v * gl_in[2].gl_Position +\n"
			"		omu * v * gl_in[3].gl_Position;\n"
			"}\n";
	}
	else if (Patch_vertices() == 3) {
		tese_shader = version_info + tese_layout +
			"void main(void) {\n"
			"	float a = gl_TessCoord.x;\n"
			"	float b = gl_TessCoord.y;\n"
			"	float c = gl_TessCoord.z;\n"
			"	gl_Position = a * gl_in[0].gl_Position +\n"
			"		b * gl_in[1].gl_Position +\n"
			"		c * gl_in[2].gl_Position;\n"
			"}\n";
	}
	


	/**
	 * 普通直线图元shader
	 */
	std::shared_ptr<ShaderProgram> shader_program = std::make_shared<ShaderProgram>();
	shader_program->attach_vertex_shader(vertex_shader);
	shader_program->attach_fragment_shader(fragment_shader);
	shader_program->attach_tess_control_shader(tesc_shader);
	shader_program->attach_tess_evaluation_shader(tese_shader);
	shader_program->link();
	return shader_program;
}

void Tessellation::Patch_vertices(GLuint val) {
	glPatchParameteri(GL_PATCH_VERTICES, val);
	patch_vertices_ = val;
}

