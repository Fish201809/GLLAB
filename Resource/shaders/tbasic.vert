#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 2) in vec2 vCord;

uniform mat4 uViewMatrix;
uniform mat4 uProjectMatrix;
uniform mat4 uModelMatrix;


out vec2 fCord;

void main(){ 
    gl_Position = uProjectMatrix * uViewMatrix * uModelMatrix * vPosition;
    fCord = vCord;
}