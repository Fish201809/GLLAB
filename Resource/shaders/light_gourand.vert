#version 450 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vCoord;
layout(location = 3) in vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectMatrix;

uniform vec3 uLightPosition;	
uniform vec3 uLightColor;

out vec3 fColor;	//片段颜色


void main(){
	vec4 view_position = uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f);
	gl_Position = uProjectMatrix * view_position;

	vec3 normal = normalize(mat3(transpose(inverse(uViewMatrix * uModelMatrix))) * vNormal);
	vec3 light_position = vec3(uViewMatrix * vec4(uLightPosition, 1.0f));
	vec3 light_direction = normalize(light_position - view_position.xyz);

	//计算环境光
	float ambient_strength = 0.1f;
	vec3 ambient_influence = ambient_strength * vColor * uLightColor;
	//计算漫反射
	vec3 diffuse_influence = dot(light_direction, normal) * vColor * uLightColor;
	
	//计算镜面反射
	vec3 specular_influence = max(dot(normalize(reflect(-light_direction, normal)), normalize(-view_position.xyz)), 0.0f) * vColor * uLightColor;
	
	fColor = ambient_influence + diffuse_influence + specular_influence;
	fColor = specular_influence;
}