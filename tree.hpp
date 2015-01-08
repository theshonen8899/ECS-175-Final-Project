/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _TREE_HPP_
#define _TREE_HPP_


/*
 Tree class (singleton)
 */
class Tree
{
private:
    static unsigned int m_vertexbuffer[3];
    static unsigned int m_texture;
    Tree();
    ~Tree();
public:
    static Tree& init();
    static void drawTree(unsigned int m_program);
    static int size;
};




#endif

