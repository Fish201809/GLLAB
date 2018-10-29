#version 450 core

in vec3 fColor;
in vec3 fNormal;

out vec4 Color;
uniform vec3 lColor;

void main(){
	
	float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lColor;

    vec3 result = ambient * fColor;

	//Color = vec4(result, 1.0f );
	Color = vec4(fColor, 1.0f );

}