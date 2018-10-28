#version 450 core

in vec2 fCord;
out vec4 Color;

uniform sampler2D MTexture0;

void main(){
	
	Color = texture(MTexture0, fCord);
	float avg_color = (Color.r + Color.g + Color.b) / 3;
	Color = vec4(avg_color, avg_color, avg_color, 1.0f);
}