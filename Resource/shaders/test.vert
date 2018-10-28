﻿#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model_matrix;
uniform mat4 vp_matrix;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = vp_matrix * model_matrix * vec4(aPos, 1.0);
}