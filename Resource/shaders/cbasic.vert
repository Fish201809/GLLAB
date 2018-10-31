#version 450 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vCoord;
layout (location = 3) in vec3 vNormal;

uniform mat4 uViewMatrix;
uniform mat4 uProjectMatrix;

uniform mat4 uModelMatrix;

out vec3 fColor;
out vec2 fCoord;
out vec3 fNormal;
out vec3 fPosition;


void main(){ 
    gl_Position = uProjectMatrix * uViewMatrix* uModelMatrix * vec4(vPosition,1.0f);
    fColor = vColor;
	fCoord = vCoord;
	//计算法线矩阵-逆矩阵的转置
	fNormal = mat3(transpose(inverse(uModelMatrix))) * vNormal;
	fPosition = vec3(uModelMatrix * vec4(vPosition, 1.0f));
}