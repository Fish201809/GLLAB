#version 450 core

layout (location = 0) in vec2 vPosition;
layout (location = 2) in vec2 vCord;

out vec2 fCord;

void main(){ 
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0f,1.0f);
	fCord = vCord;
}