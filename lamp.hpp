/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _LAMP_HPP_
#define _LAMP_HPP_


/*
 Lamp class (singleton)
 */
class Lamp
{
private:
    static unsigned int m_vertexbuffer[3];
    Lamp();
    ~Lamp();
public:
    static Lamp& init();
    static void drawLamp(unsigned int m_program);
    static int size;
};




#endif

