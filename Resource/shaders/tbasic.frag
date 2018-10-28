#version 450 core

out vec4 Color;
in vec2 fCord;

uniform sampler2D ourTexture;

void main(){	
	Color = texture(ourTexture, fCord);
}