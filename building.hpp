/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _BUILDING_HPP_
#define _BUILDING_HPP_
#include "bitmap/bitmap.h"

/*
 Building class (singleton)
 */
class Building
{
private:
    static unsigned int m_vertexbuffer;
    static unsigned int* m_texture;
    static void loadTexture(unsigned int, CBitmap image);
    Building();
    ~Building();
public:
    static Building& init();
    static void drawBuilding(unsigned int m_program);
    static int size;
};




#endif

