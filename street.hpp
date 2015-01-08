/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _STREET_HPP_
#define _STREET_HPP_


/*
 Street class (singleton)
 */
class Street
{
private:
    static unsigned int m_vertexbuffer;
    static unsigned int m_texture;
    Street();
    ~Street();
public:
    static Street& init();
    static void drawStreet(unsigned int m_program);
    static int size;
};




#endif

