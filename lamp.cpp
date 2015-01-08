/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
*/

#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else
#include <GL/glew.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "lamp.hpp"
using namespace std;
unsigned int Lamp::m_vertexbuffer[3];
int Lamp::size;
/*
 Construct cube - initialize vertex buffer object
 */
Lamp::Lamp()
{
    std::vector<float> data;
    std::vector<float> tempdata;
    std::vector<float> normals;
    std::vector<float> tempnormals;
    std::vector<float> texture;
    std::vector<float> temptexture;
    std::ifstream File("lamp.obj");
    string Line;
    string Name;
    string N2;
    int i=0;
    bool texskip=0;
    while(std::getline(File, Line)){
      if(Line == "" || Line[0] == '#')
        continue;

      std::istringstream LineStream(Line);
			LineStream >> Name >> N2;
      
      if(Name == "usemtl"&&N2== "car_glass.tga")
        texskip=1;
        
      if(Name == "v"){// Vertex
	    float Vertex[3];
	    i++;
	    
	    sscanf(Line.c_str(), "%*s %f %f %f", &Vertex[0], &Vertex[1], &Vertex[2]);
	    //if(i==2114)
	     //   cout<<i<<" "<<Vertex[0]<<" "<<Vertex[1]<<" "<<Vertex[2]<<endl;
	    tempdata.push_back(Vertex[0]);
	    tempdata.push_back(Vertex[1]);
	    tempdata.push_back(Vertex[2]);
      }
       else if(Name =="f"){
         int v1,t1,n1,v2,t2,n2,v3,v4,t3,n3;
       
         sscanf(Line.c_str(), "%*s %d %d %d %d", &v1, &v2, &v3, &v4);
        v1-=1;v2-=1;v3-=1;v4-=1;//n2-=1;n3-=1,t1-=1,t2-=1,t3-=1;
       // cout<<i<<" " <<tempdata[v1*3] <<" "<< " "<< tempdata[v1*3+1] << " " << tempdata[v1*3+2]<<endl;
        data.push_back(tempdata[v1*3]),data.push_back(tempdata[v1*3+1]),data.push_back(tempdata[v1*3+2]);
        data.push_back(tempdata[v2*3]),data.push_back(tempdata[v2*3+1]),data.push_back(tempdata[v2*3+2]);
        data.push_back(tempdata[v3*3]),data.push_back(tempdata[v3*3+1]),data.push_back(tempdata[v3*3+2]);
   data.push_back(tempdata[v4*3]),data.push_back(tempdata[v4*3+1]),data.push_back(tempdata[v4*3+2]);
       /* normals.push_back(tempnormals[n1*3]),normals.push_back(tempnormals[n1*3+1]),normals.push_back(tempnormals[n1*3+2]);
        normals.push_back(tempnormals[n2*3]),normals.push_back(tempnormals[n2*3+1]),normals.push_back(tempnormals[n2*3+2]);
        normals.push_back(tempnormals[n3*3]),normals.push_back(tempnormals[n3*3+1]),normals.push_back(tempnormals[n3*3+2]);
        if(!texskip){
            texture.push_back(temptexture[t1*3]),texture.push_back(1+temptexture[t1*3+1]),texture.push_back(temptexture[t1*3+2]);
            texture.push_back(temptexture[t2*3]),texture.push_back(1+temptexture[t2*3+1]),texture.push_back(temptexture[t2*3+2]);
            texture.push_back(temptexture[t3*3]),texture.push_back(1+temptexture[t3*3+1]),texture.push_back(temptexture[t3*3+2]);
        }//cout<<temptexture[t1*3]<<" "<<temptexture[t1*3+1]<<" "<<temptexture[t1*3+2]<<endl;*/
        }
    }
    size=data.size()*sizeof(float);
    glGenBuffers(1, m_vertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW); //set buffer data
    
  
    
   /*glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), normals.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1); //attribute 1 in shader is normals
    
        
   glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[2]);
    glBufferData(GL_ARRAY_BUFFER, texture.size()*sizeof(float), texture.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2); //attribute 2 in shader is textures*/
    
}

/*
 Destroy Lamp - clean up geometry
 */
Lamp::~Lamp()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, m_vertexbuffer);
}


/*
 Draw Lamp
 */
void Lamp::drawLamp(unsigned int m_program)
{
	//	glUseProgram(m_program);
	  glTranslatef(0,45,0);
		glRotatef(90,1,0,0);
		glScalef(4.0,4.0,4.0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[0]);  
  glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0); //attribute 0 in shader is positions       
    glDrawArrays(GL_QUADS, 0, size/3);      // draw cube
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  //  glUseProgram(m_program);
}



Lamp& Lamp::init()
{
    static Lamp c;
    return c;
}
