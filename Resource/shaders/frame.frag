#version 450 core

in vec2 fCord;
out vec4 Color;

uniform sampler2D MTexture0; 

void main(){
	Color = texture(MTexture0, fCord);
}