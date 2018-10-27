#version 450 core

out vec4 color;
in vec3 Fcolor;
in vec2 fCord;

uniform sampler2D ourColor;

void main(){	
	color = texture(ourColor, fCord);
	//color = vec4(fCord, 0.0f, 1.0f);
}