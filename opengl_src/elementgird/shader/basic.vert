#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vColor;

uniform mat4 project;
uniform mat4 model_matrix;

out vec3 fColor;

void main(){
    gl_Position = project * model_matrix * vPosition;
    fColor = vColor;
}