#version 450 core

//冯氏着色(Phong Shading)
in vec3 fColor;
in vec3 fNormal;
in vec3 fPosition;

out vec4 Color;
uniform vec3 ulight_color;	//光源颜色
uniform vec3 ulight_position;	//光源位置
uniform vec3 ucamera_position;	//相机位置

void main(){
	
	//环境光
	float ambient_strength = 0.2;
    vec3 ambient = ambient_strength * ulight_color;
  
    vec3 light_direction = ulight_position - fPosition;
	vec3 camera_direction = normalize(ucamera_position - fPosition);
	vec3 normal = normalize(fNormal);
	light_direction = normalize(light_direction);

	//漫反射
	float diff = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = diff * ulight_color;


	//镜面反射
	float specular_strength = 0.5;
	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(camera_direction, reflect_direction), 0.0), 32);
	vec3 specular = specular_strength * spec * ulight_color;

	vec3 result = (ambient + diffuse + specular) * fColor;

	Color = vec4(result, 1.0f );
}