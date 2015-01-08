/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _CAR_HPP_
#define _CAR_HPP_


/*
 Car class (singleton)
 */
class Car
{
private:
    static unsigned int m_vertexbuffer[3];
    static unsigned int m_texture;
    Car();
    ~Car();
public:
    static Car& init();
    static void drawCar(unsigned int);
    static int size;
    
};




#endif

