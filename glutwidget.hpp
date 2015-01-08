/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
 */
#ifndef _GLUTWIDGET_HPP_
#define _GLUTWIDGET_HPP_

class Car;
class Car2;
class Ped;
class Tree;
class Lamp;
class Building;
class Street;
class House;
class Skybox;
class Point
	{
	public:
		Point(){};
		Point(double ix,double iy,double iz)
			{
			x=ix;
			y=iy;
			z=iz;
			}
		double x;
		double y;
		double z;
	};

/*
 GLUT widget singleton
 */
class glutWidget
{
private:
    static Car *c;
    static Car2 *c2;
    static Tree *t;
    static Ped *p;
    static Lamp *l;
    static Building *b;
    static Street *e;
    static House *h;
    static Skybox *s;
    static unsigned int m_program;                 //shader program
    static unsigned int m_vertexsh;                //vertex shader
    static unsigned int m_fragmentsh;              //fragment shader
    static unsigned int m_frame;
    static const unsigned int m_width = 500;
    static const unsigned int m_height = 500;
    static void render();
    static void update();
       static void mouseMotion(int,int);
    static void mouseButton(int,int,int,int);
    static void keyUp(unsigned char key, int, int);
    static void stop();
    static void initOpenGL();
    static void drawCars();
    static void makeShaders();
    static void update(int value);
    glutWidget(int argc, char **argv);
    static void normalize(Point*);
    static Point* crossproduct(Point,Point);
    
public:
    static glutWidget& init(int argc, char **argv)
    {
        static glutWidget gw(argc, argv);
        return gw;
    }
    static void run();
};





#endif

