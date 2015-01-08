/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _CAR2_HPP_
#define _CAR2_HPP_


/*
 Car2 class (singleton)
 */
class Car2
{
private:
    static unsigned int m_vertexbuffer[3];
    static unsigned int m_texture;
    Car2();
    ~Car2();
public: 
    static Car2& init();
    static void drawCar2(unsigned int);
    static int size;
    
};




#endif

