#version 120
 
varying  vec3 ex_Normal; //normals as computed in vertex shader
varying vec3 ex_Texture;
uniform sampler2D col_tex;
void main(void)
{
	float d = .3 + max(dot(ex_Normal,vec3(5.0,8.8,0.0)),0.0)/2; 	//basic, fake lighting
    gl_FragColor = d*texture2D(col_tex,ex_Texture.st);
    //gl_FragColor=vec4(ex_Texture.st,0.0,1.0);
}
