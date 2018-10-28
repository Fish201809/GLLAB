#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 2) in vec2 vCord;

uniform mat4 vp_matrix;
uniform mat4 model_matrix;

out vec2 fCord;

void main(){ 
    gl_Position = vp_matrix * model_matrix * vPosition;
    fCord = vCord;
}