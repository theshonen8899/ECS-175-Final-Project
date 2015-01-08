/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _PED_HPP_
#define _PED_HPP_


/*
 Ped class (singleton)
 */
class Ped
{
private:
    static unsigned int m_vertexbuffer[3];
    static unsigned int m_texture;
    Ped();
    ~Ped();
public:
    static Ped& init();
    static void drawPed(unsigned int);
    static int size;
    
};




#endif

