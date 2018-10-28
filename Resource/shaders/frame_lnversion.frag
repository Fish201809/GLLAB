#version 450 core

in vec2 fCord;
out vec4 Color;
uniform sampler2D MTexture0;

void main(){
	Color = vec4(vec3(1.0f - texture(MTexture0, fCord)), 1.0f);
}