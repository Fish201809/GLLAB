#version 450 core                                                                 
                                                                                  
layout (vertices = 4) out;           
uniform float outer_0;
uniform float outer_1;
uniform float outer_2;
uniform float outer_3;
                                                                                  
void main(void)                                                                   
{                                                                                 	
    if (gl_InvocationID == 0)                                                     
    {                                                                             	
        gl_TessLevelOuter[0] = outer_0;                                               
        gl_TessLevelOuter[1] = outer_1;   
		gl_TessLevelOuter[2] = outer_2;                                               
        gl_TessLevelOuter[3] = outer_3;              
    }                                                                             
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     	
}    
