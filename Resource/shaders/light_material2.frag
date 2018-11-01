#version 450 core

in vec3 fPosition;	//传递到观察空间的片元坐标
in vec3 fColor;
in vec3 fCoord;
in vec3 fNormal; //法线矩阵变换后的法线
in vec3 fLightPosition; //传递到观察空间的光源坐标

uniform vec3 uLightColor;

out vec4 Color;


struct Material{
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	float shininess;
};

struct LightMaterial{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material uMaterial;
uniform LightMaterial uLightMaterial;

void main(){
	vec3 normal = normalize(fNormal);
	vec3 light_direction = normalize(fLightPosition - fPosition);
	vec3 reflect_direction = normalize(reflect(-light_direction, normal));
	vec3 camera_direction = normalize(-fPosition);

	//计算环境光
	float ambient_strength = 0.1f;
	vec3 ambient_influence = ambient_strength * uLightMaterial.ambient * uMaterial.ambient_color;

	//计算漫反射光
	float diffuse_strength = 0.5f;
	vec3 diffuse_influence = max(dot(normal, light_direction), 0.0f) * diffuse_strength * uLightMaterial.diffuse * uMaterial.diffuse_color;

	//计算镜面反射
	float specular_strength = 0.8f;
	vec3 specular_influence = pow(max(dot(reflect_direction , camera_direction), 0.0f), 32) * 
									specular_strength * uLightMaterial.specular * uMaterial.specular_color;
	Color = vec4(ambient_influence + diffuse_influence + specular_influence, 1.0f);
	//Color = vec4(ambient_influence,1.0f) * vec4(fColor, 1.0f);	//环境光效果
	//Color = vec4(diffuse_influence, 1.0f) * vec4(fColor, 1.0f);	//漫反射效果
	//Color = vec4(specular_influence,1.0f) * vec4(fColor, 1.0f);	//镜面反射效果
}