#version 450 core

//冯氏着色(Phong Shading)
in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 Color;
uniform vec3 ulight_color;
uniform vec3 ulight_position;
uniform vec3 ucamera_position;

void main(){
	
	//环境光
	float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * ulight_color;
  
    vec3 light_direction = ulight_position - fPosition;
	vec3 viewDir = normalize(ucamera_position - fPosition);
	vec3 normal = normalize(fNormal);
	light_direction = normalize(light_direction);

	//漫反射
	float diff = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = diff * ulight_color;


	//镜面反射
	float specularStrength = 0.5;
	vec3 reflectDir = reflect(-light_direction, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * ulight_color;

	vec3 result = (ambient + diffuse + specular) * fColor;
	Color = vec4(result, 1.0f );
}