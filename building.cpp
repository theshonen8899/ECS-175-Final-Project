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
#include "building.hpp"
#include "bitmap/bitmap.h"
using namespace std;
unsigned int Building::m_vertexbuffer;
unsigned int* Building::m_texture;
int Building::size;
/*
 Construct cube - initialize vertex buffer object
 */
Building::Building()
{
	CBitmap* image[6];
	CBitmap front("texture.bmp");
	CBitmap back("texture.bmp");
	CBitmap right("texture.bmp");
	CBitmap left("texture.bmp");
	CBitmap top("broof.bmp");
	CBitmap bottom("texture.bmp");
	image[0]=&front,image[1]=&back,image[2]=&right,image[3]=&left,image[4]=&top,image[5]=&bottom;
   m_texture = new unsigned int[6];
    glGenTextures(6, m_texture);  
    for(unsigned int i=0;i<6;i++){
	glBindTexture(GL_TEXTURE_2D, m_texture[i]);    //bind this texture to be active

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image[i]->GetWidth(),image[i]->GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image[i]->GetBits()); //load data into texture
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //specify minificaton filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //specify magnificaton filtering

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    //specify texture coordinate treatment
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);    //specify texture coordinate treatment
	glEnable(GL_TEXTURE_2D);
	}
}

/*
 Destroy Building - clean up geometry
 */
Building::~Building()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(6, m_texture);
    delete[] m_texture;
}


/*
 Draw Building
 */
void Building::drawBuilding(unsigned int m_program)
{

	 int location = glGetUniformLocation(m_program, "col_tex");
    glBindTexture(GL_TEXTURE_2D,m_texture[0]);
    glUniform1i(location,GL_TEXTURE_2D);
 	 glBegin(GL_QUADS);
		//glNormal3d(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex3f(  0.5, 0.0, -0.495 );
		glTexCoord2f(0, 1);
		glVertex3f(  0.5,  2, -0.495 );
		glTexCoord2f(1, 1);
		glVertex3f( -0.5,  2, -0.495 );
		glTexCoord2f(1, 0);
		glVertex3f( -0.5, 0.0, -0.495 );
	 glEnd();
	 
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	   glUniform1i(location,GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		//glNormal3d(0, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3f(  0.5, 0.0, 0.495 );
		glTexCoord2f(0, 1);
		glVertex3f(  0.5,  2, 0.495 );
		glTexCoord2f(1, 1);
		glVertex3f( -0.5,  2, 0.495 );
		glTexCoord2f(1, 0);
		glVertex3f( -0.5, 0.0, 0.495 );
	glEnd();
	 
	glBindTexture(GL_TEXTURE_2D, m_texture[2]);
		   glUniform1i(location,GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		//glNormal3d(1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f( 0.495, 0.0, -0.5 );
		glTexCoord2f(0, 1);
		glVertex3f( 0.495,  2, -0.5 );
		glTexCoord2f(1, 1);
		glVertex3f( 0.495,  2,  0.5 );
		glTexCoord2f(1, 0);
		glVertex3f( 0.495, 0.0,  0.5 );
	glEnd();
	 
	 glBindTexture(GL_TEXTURE_2D, m_texture[3]);
	  glUniform1i(location,GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		//glNormal3d(-1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f( -0.495, 0.0,  0.5 );
		glTexCoord2f(0, 1);
		glVertex3f( -0.495,  2,  0.5 );
		glTexCoord2f(1, 1);
		glVertex3f( -0.495,  2, -0.5 );
		glTexCoord2f(1, 0);
		glVertex3f( -0.495, 0.0, -0.5 );
	glEnd();

	//roof
	glBindTexture(GL_TEXTURE_2D, m_texture[4]);
	  glUniform1i(location,GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		//glNormal3d(0, 1, 0);
		glTexCoord2f(0, 0);
		glVertex3f(  0.5,  2,  0.5 );
		glTexCoord2f(0, 1);
		glVertex3f(  0.5,  2, -0.5 );
		glTexCoord2f(1, 1);
		glVertex3f( -0.5,  2, -0.5 );
		glTexCoord2f(1, 0);
		glVertex3f( -0.5,  2,  0.5 );
	glEnd();
}



Building& Building::init()
{
    static Building c;
    return c;
}
