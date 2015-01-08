#version 120
 
attribute  vec3 in_Position;	//attribute 0 of VBO: positions of vertices
attribute  vec3 in_Normal;	//attribute 1 of VBO: normals
attribute  vec3 in_Texture;
varying vec3 ex_Normal;		//this is passed to fragment shader for "lighting"
varying vec3 ex_Texture;

void main(void)
{
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(in_Position, 1.0);  	//rotate, translate, and project positions - not 1.0 w component     
    ex_Normal = vec3(gl_ModelViewMatrix*vec4(in_Normal,0.0));	//rotate normals - note 0.0 w component 
    ex_Texture=in_Texture;
}
