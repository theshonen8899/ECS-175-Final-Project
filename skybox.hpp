/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _SKYBOX_HPP_
#define _SKYBOX_HPP_
#include "bitmap/bitmap.h"

/*
 Skybox class (singleton)
 */
class Skybox
{
private:
    static unsigned int m_vertexbuffer;
    static unsigned int* m_texture;
    static void loadTexture(unsigned int, CBitmap image);
    Skybox();
    ~Skybox();
public:
    static Skybox& init();
    static void drawSkybox(unsigned int m_program);
    static int size;
};




#endif

