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
#include <cstring>
#include "bitmap/bitmap.h"

#include "car2.hpp"
using namespace std;
unsigned int Car2::m_texture;
unsigned int Car2::m_vertexbuffer[3];
int Car2::size;
/*
 Construct cube - initialize vertex buffer object
 */
Car2::Car2()
{
    std::vector<float> data;
    std::vector<float> tempdata;
    std::vector<float> normals;
    std::vector<float> tempnormals;
    std::vector<float> texture;
    std::vector<float> temptexture;
    std::ifstream File("car_white.obj");
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
      else if(Name == "vn"){
        float Normal[3];
         sscanf(Line.c_str(), "%*s %f %f %f", &Normal[0], &Normal[1], &Normal[2]);
         tempnormals.push_back(Normal[0]);
         tempnormals.push_back(Normal[1]);
         tempnormals.push_back(Normal[2]);
         }
      else if(Name == "vt"){
         float Texture[3];
         sscanf(Line.c_str(), "%*s %f %f %f", &Texture[0], &Texture[1], &Texture[2]);
         temptexture.push_back(Texture[0]);
         temptexture.push_back(Texture[1]);
         temptexture.push_back(Texture[2]);
         }
       else if(Name =="f"){
         int v1,t1,n1,v2,t2,n2,v3,t3,n3;
       
         sscanf(Line.c_str(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
        v1-=1;v2-=1;v3-=1;n1-=1;n2-=1;n3-=1,t1-=1,t2-=1,t3-=1;
       // cout<<i<<" " <<tempdata[v1*3] <<" "<< " "<< tempdata[v1*3+1] << " " << tempdata[v1*3+2]<<endl;
        data.push_back(tempdata[v1*3]),data.push_back(tempdata[v1*3+1]),data.push_back(tempdata[v1*3+2]);
        data.push_back(tempdata[v2*3]),data.push_back(tempdata[v2*3+1]),data.push_back(tempdata[v2*3+2]);
        data.push_back(tempdata[v3*3]),data.push_back(tempdata[v3*3+1]),data.push_back(tempdata[v3*3+2]);
        normals.push_back(tempnormals[n1*3]),normals.push_back(tempnormals[n1*3+1]),normals.push_back(tempnormals[n1*3+2]);
        normals.push_back(tempnormals[n2*3]),normals.push_back(tempnormals[n2*3+1]),normals.push_back(tempnormals[n2*3+2]);
        normals.push_back(tempnormals[n3*3]),normals.push_back(tempnormals[n3*3+1]),normals.push_back(tempnormals[n3*3+2]);
        if(!texskip){
            texture.push_back(temptexture[t1*3]),texture.push_back(1+temptexture[t1*3+1]),texture.push_back(temptexture[t1*3+2]);
            texture.push_back(temptexture[t2*3]),texture.push_back(1+temptexture[t2*3+1]),texture.push_back(temptexture[t2*3+2]);
            texture.push_back(temptexture[t3*3]),texture.push_back(1+temptexture[t3*3+1]),texture.push_back(temptexture[t3*3+2]);
        }//cout<<temptexture[t1*3]<<" "<<temptexture[t1*3+1]<<" "<<temptexture[t1*3+2]<<endl;
        }
    }
    size=data.size()*sizeof(float);
    glGenBuffers(3, m_vertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW); //set buffer data
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), normals.data(), GL_STATIC_DRAW);
   
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[2]);
    glBufferData(GL_ARRAY_BUFFER, texture.size()*sizeof(float), texture.data(), GL_STATIC_DRAW);
    
    CBitmap image("bluecar.bmp");               //read bitmap image
    
    glGenTextures(1,&m_texture);                //allocate 1 texture
    glBindTexture(GL_TEXTURE_2D, m_texture);    //bind this texture to be active
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.GetWidth(),image.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.GetBits()); //load data into texture
        
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //specify minificaton filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //specify magnificaton filtering

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    //specify texture coordinate treatment
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);    //specify texture coordinate treatment
    
}

/*
 Destroy Car2 - clean up geometry
 */
Car2::~Car2()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(3, m_vertexbuffer);
}


/*
 Draw Car2
 */
void Car2::drawCar2(unsigned int m_program)
{
	 int location = glGetUniformLocation(m_program, "col_tex");
    glBindTexture(GL_TEXTURE_2D,m_texture);
    glUniform1i(location,GL_TEXTURE_2D);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[0]);    
     glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(0); //attribute 0 in shader is positions
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer[1]);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1); //attribute 1 in shader is normals
    
        
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexbuffer[2]);
    glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2); //attribute 2 in shader is textures
    glDrawArrays(GL_TRIANGLES, 0, size/3);      // draw cube
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	  glDisableVertexAttribArray(2);
    
}



Car2& Car2::init()
{
    static Car2 c;
    return c;
}
