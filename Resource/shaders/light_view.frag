#version 450 core

in vec3 fPosition;	//传递到观察空间的片元坐标
in vec3 fNormal; //法线矩阵变换后的法线
in vec3 fLightPosition; //传递到观察空间的光源坐标


uniform in vec3 uLightColor;

void main(){
	vec3 normal = normalize(fNormal);
	vec3 light_direction = normalize(fLightPosition - fPosition);

	//计算环境光
	float ambient_strength = 0.1f;
	vec3 ambient_influence = ambient_strength * uLightColor;

	//计算漫反射光
	float diffuse_strength = 0.4f;
	max(dot(light_direction ,fNormal), 0.0f) * uLightColor;
}