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
#include "street.hpp"
#include "bitmap/bitmap.h"
using namespace std;
unsigned int Street::m_vertexbuffer;
unsigned int Street::m_texture;
int Street::size;
/*
 Construct cube - initialize vertex buffer object
 */
Street::Street()
{
    CBitmap image("street.bmp");               //read bitmap image
    
    glGenTextures(1,&m_texture);                //allocate 1 texture
    glBindTexture(GL_TEXTURE_2D, m_texture);    //bind this texture to be active
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.GetWidth(),image.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.GetBits()); //load data into texture
        
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //specify minificaton filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //specify magnificaton filtering

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    //specify texture coordinate treatment
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);    //specify texture coordinate treatment
    glEnable(GL_TEXTURE_2D);    //enable texturing
    
}

/*
 Destroy Street - clean up geometry
 */
Street::~Street()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_vertexbuffer);
}


/*
 Draw Street
 */
void Street::drawStreet(unsigned int m_program)
{
	 int location = glGetUniformLocation(m_program, "col_tex");
    glBindTexture(GL_TEXTURE_2D,m_texture);
    glUniform1i(location,GL_TEXTURE_2D);
	 
	  glBegin(GL_QUADS);
	  glTexCoord2f(1, 0);
	  glVertex3f(  1, 0, 0 );
	  glTexCoord2f(1, 1);
	  glVertex3f(  1, 0,  1 );
	  glTexCoord2f(0, 1);
	  glVertex3f( 0, 0,  1 );
	  glTexCoord2f(0, 0);
	  glVertex3f( 0, 0, 0 );
	  glEnd();
    
}



Street& Street::init()
{
    static Street c;
    return c;
}
