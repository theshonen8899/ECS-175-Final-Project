/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _HOUSE_HPP_
#define _HOUSE_HPP_
#include "bitmap/bitmap.h"

/*
 House class (singleton)
 */
class House
{
private:
    static unsigned int m_vertexbuffer;
    static unsigned int* m_texture;
    static void loadTexture(unsigned int, CBitmap image);
    House();
    ~House();
public:
    static House& init();
    static void drawHouse(unsigned int m_program);
    static int size;
};




#endif

