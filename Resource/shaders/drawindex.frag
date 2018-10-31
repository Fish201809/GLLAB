#version 450 core


uniform uint uIndex;

//out vec4 Color;
//out uvec3 Color;

//out int Color;

out uint Color;

void main(){
	Color =  uIndex;
	//Color = vec4(0.0f, 0.0f,0.0f, 1.0f);
	//Color = vec4(ured, ugreen, ublue, 1);
	//Color = vec4(0.1f, 0.2f, 0.3f,1.0f);
}


