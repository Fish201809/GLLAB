#version 450 core

out vec4 Color;
in vec3 fColor;

void main(){	
	Color = vec4(fColor, 1.0f);
}