#version 450 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vCoord;
layout(location = 3) in vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectMatrix;
uniform vec3 uLightPosition;	


out vec3 fPosition;	//传递到观察空间的片元坐标
out vec3 fColor;	//片段颜色
out vec3 fCoord;
out vec3 fNormal; //法线矩阵变换后的法线
out vec3 fLightPosition; //传递到观察空间的光源坐标


void main(){
	gl_Position = uProjectMatrix * uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f);
	
	fPosition = vec3(uViewMatrix * uModelMatrix * vec4(vPosition, 1.0f));
	fColor = vColor;
	fCoord = vCoord;
	fNormal = mat3(transpose(inverse(uViewMatrix * uModelMatrix))) * vNormal;
	fLightPosition = vec3(uViewMatrix * vec4(uLightPosition, 1.0f));
}
