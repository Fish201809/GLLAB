#version 450 core

in vec2 fCord;
out vec4 Color;

uniform sampler2D MTexture0;

void main(){
	
	Color = texture(MTexture0, fCord);
	float avg_color = (0.2126 * Color.r + 0.7152 * Color.g +  0.0722 * Color.b) / 3;
	Color = vec4(avg_color, avg_color, avg_color, 1.0f);
}