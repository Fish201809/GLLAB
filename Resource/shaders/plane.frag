#version 450 core

out vec4 color;
in vec3 fColor;
in vec2 fCord;

uniform sampler2D ourTexture;

void main(){	
	color = texture(ourTexture, fCord);
	//color = vec4(fCord, 0.0f, 1.0f);
}