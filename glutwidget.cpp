/*
 
 ECS 175: Computer Graphics
 UC Davis, Spring 2013
 
 Demo 4
 
*/

#ifdef __APPLE__
#include <GL/glew.h>
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cstring>
#include "bitmap/bitmap.h"
#include "glutwidget.hpp"
#include "shader_utils.hpp"
#include "car.hpp"
#include "ped.hpp"
#include "tree.hpp"
#include "lamp.hpp"
#include "math.h"
#include "building.hpp"
#include "street.hpp"
#include "house.hpp"
#include "skybox.hpp"
#include "car2.hpp"

unsigned int glutWidget::m_frame;
unsigned int glutWidget::m_program;               
unsigned int glutWidget::m_vertexsh;
unsigned int glutWidget::m_fragmentsh;  
Car *glutWidget::c;
Ped *glutWidget::p;
Tree *glutWidget::t;
Car2 *glutWidget::c2;
Lamp *glutWidget::l;
Building *glutWidget::b;
Street *glutWidget::e;
House *glutWidget::h;
Skybox *glutWidget::s;
unsigned int m_texture;
int freemode=0;
float x=0;
float y=40;
float z=-100;
float carcamx=0;float carcamy=0;float carcamz=0;
float car2x=-550;float car2y=0;float car2z=-600;
float trans2x=0;float trans2y=0;float trans2z=0;
float dx=0;float dy=0;float dz=0;
float phi = asin(y/sqrt(x*x+y*y+z*z)); 
float tau = -acos(x/sqrt(x*x+z*z+y*y)/cos(phi));
float zoom=1;
float flip=1;
float transx=0;
float transy=0;
float transz=0;
float rotatey=0; float rotate2y=0;
int xcurr;
int ycurr;
int frame = 0;
int carmode = 0;

/*
 Initializes GLUT context
 */
glutWidget::glutWidget(int argc, char** argv)
{
    m_frame = 0;
    glutInitWindowSize(glutWidget::m_width, glutWidget::m_height);
    glutInit(&argc,argv);
    glutInitDisplayString("samples rgb double depth");
    glutCreateWindow("ECS 175 Demo 4");
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton); 
    glutTimerFunc(50,update,0);       //what to call when no user input given
    glutKeyboardUpFunc(keyUp);  //what to call when user releases a key
    glutDisplayFunc(render);    //what to call when window needs redrawing
    glutIdleFunc(update);       //what to call when no user input given
    initOpenGL();
}


/*
 Initializes opengl states
 */
void glutWidget::initOpenGL()
{
    glewExperimental = GL_TRUE; 
    glewInit();                             //initialize GLEW - this enables us to use extensions
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //default "empty"/background color is set to white
    
   // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    makeShaders();    
    l = &Lamp::init();
    t = &Tree::init();
    p = &Ped::init();
    c = &Car::init();
    b = &Building::init();
    e = &Street::init();
    h = &House::init();
    s = &Skybox::init();
    c2 = &Car2::init();
}




/*
 Draws four Cars
 */
void glutWidget::drawCars()
{
    glEnable(GL_TEXTURE_2D);    //enable texturing
    glBindTexture(GL_TEXTURE_2D,m_texture);
    glUseProgram(m_program);    //enable use of shader
    glActiveTexture(GL_TEXTURE0);
    glPushMatrix();
    glTranslatef(transx-60,transy,transz);
   
    glScalef(.2,.2,.2);
    glRotatef(rotatey,0,1,0);
    c->drawCar(m_program);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(car2x+trans2x,car2y+trans2y,car2z+trans2z);
   
    glScalef(.2,.2,.2);
    glRotatef(rotate2y,0,1,0);
    c2->drawCar2(m_program);
    glPopMatrix();
    glUseProgram(0);    //disable use of shader
    
       
}

/*
    Redraws window contents
 */

void glutWidget::render()
{
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) m_width / m_height;
    gluPerspective(45, aspect, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(freemode==1)
    	gluLookAt(x+dx,y+dy,z+dz,
    				dx,dy,dz,
    				0,1,0);
 	 else if(carmode==0)
     gluLookAt(carcamx+x+transx-60, carcamy+y+transy, carcamz+z+transz,
            carcamx+transx-60,carcamy+transy,carcamz+transz,
              0.0f,flip, 0.0f);
           //set up camera position and orientation    
     else if(carmode==1)
     gluLookAt(carcamx+x+trans2x, carcamy+y+trans2y, carcamz+z+trans2z,
            carcamx+trans2x,carcamy+trans2y,carcamz+trans2z,
              0.0f,flip, 0.0f);
           //set up camera position and orientation    
     glPushMatrix();
		// glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
     glScalef(2000.0,2000.0,2000.0);
     s->drawSkybox(m_program);
		// glDisable(GL_CULL_FACE);
     glPopMatrix();
     
//draw buildings
	glPushMatrix();
	glTranslatef(100.0,0.0, 550.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100.0,0.0, 400.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100.0,0.0, 250.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100.0,0.0,100.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

for(int i = 0; i < 5; i++){
	glPushMatrix();
	glTranslatef(100.0,0.0, -(i*150 + 200.0));
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();
}//for

	glPushMatrix();
	glTranslatef(250.0,0.0, 550.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0,0.0, 400.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0,0.0, 250.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0,0.0,100.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

for(int i = 0; i < 5; i++){
	glPushMatrix();
	glTranslatef(250.0,0.0, -(i*150 + 200.0));
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();
}//for

	glPushMatrix();
	glTranslatef(400.0,0.0, 550.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0,0.0, 400.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0,0.0, 250.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0,0.0,100.0);
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();

for(int i = 0; i < 5; i++){
	glPushMatrix();
	glTranslatef(400.0,0.0, -(i*150 + 200.0));
	glScalef(100.0,100.0,100.0);  
	b->drawBuilding(m_program);
	glPopMatrix();
}//for

//draw streets + lamps

	for(int i = -10; i<10; i++){
		glPushMatrix();
		glTranslatef(-90.0,0.5,i*100.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-100.0,0.0,i*100.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();
	}//for

	for(int i = 0; i<5; i++){
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-10.0,0.5, i*100 + 10.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-20.0,0.0,i*100.0 + 50.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(20.0 ,0.0,i*100.0 + 50.0);
		glScalef(0.3,0.3,0.3);  
		glRotatef(180, 0, 1, 0);
		p->drawPed(m_program);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(120.0,0.0,i*100.0 + 50.0);
		//glScalef(0,0,0);  
		t->drawTree(m_program);
		glPopMatrix();
	}//for

	for(int i = -10; i<10; i++){
		glPushMatrix();
		glTranslatef(500,0.5,i*100.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(490.0,0.0,i*100.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();
	}//for

	for(int i = -10; i<10; i++){
		glPushMatrix();
		glTranslatef(-590.0,0.5,i*100.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-600.0,0.0,i*100.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();
	}//for

	for(int i = 0; i<5; i++){
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-700.0,0.5, i*100 + 10.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-690.0,0.0,i*100.0 + 50.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();
	}//for

	for(int i = 0; i<4; i++){
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(700.0,0.5, i*100 + -490.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(690.0,0.0,i*100.0 + -500.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();
	}//for

	for(int i = 0; i<4; i++){
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-620.0,0.5, i*100 + -490.0);
		glScalef(100.0,100.0,100.0);  
		e->drawStreet(m_program);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-630.0,0.0,i*100.0 + -500.0);
		//glScalef(0,0,0);  
		l->drawLamp(m_program);
		glPopMatrix();
	}//for

//draw houses
	for(int i = 0; i<8; i++){
		glPushMatrix();
		glTranslatef(-200.0,0.0,i*150 - 600.0);
		glScalef(100.0,100.0,100.0);  
		h->drawHouse(m_program);
		glPopMatrix();
	}//for

	for(int i = 0; i<8; i++){
		glPushMatrix();
		glTranslatef(-400.0,0.0,i*150 - 600.0);
		glRotatef(180, 0, 1, 0);
		glScalef(100.0,100.0,100.0);  
		h->drawHouse(m_program);
		glPopMatrix();
	}//for

//draw car
	drawCars();
   
	glutSwapBuffers();  //swaps front and back buffer for double buffering
}

/*
 Handles user event: a key was released
 */
void glutWidget::keyUp(unsigned char key, int, int) 
{
    if(key=='q')
        stop();
    else if(key=='u')
        glutPostRedisplay();
    else if(key=='c')
        {
        freemode=0;
        carmode++;
        carmode=carmode%2;
        if(carmode==0)
        	carcamx=0,carcamy=0,carcamz=0;
        else 
        	carcamx=car2x,carcamy=car2y,carcamz=car2z;
        }
    else if(key=='f')
    	  {
    	  if (freemode==0){
    	  freemode=1;
    	  if(carmode==0)
    	 	   { dx=transx; 	  dy=transy;   dz=transz;
    	  		}
    	  else
    	  	   {
    	  	   //x=x+car2x;y+=car2y;z+=car2z;
    	  	   dx=carcamx+trans2x; dy=carcamy+trans2y; dz=carcamz+trans2z;
    	  	   }
    	  	   }
    	  }
    if (freemode==1){
         Point *origin = new Point(-x,-y,-z);
    normalize(origin);
    Point *cross = crossproduct(Point(-x,-y,-z),Point(0,1,0));//Point(-x,-y,-z) is vector from camera to origin
    //Cross at this point is normal to the vertical plane of the viewing angle
    Point *normal = crossproduct(Point(-x,-y,-z),*cross);
	 normalize(normal);//This is vertical in respect to viewing perspective
	 cross = crossproduct(Point(x,y,z),*normal);
	 normalize(cross);//This is horizontal in respect to viewing perspective 
	      if(key=='s')
	      	{
	      	dx-=origin->x*4;
	      	dy-=origin->y*4;
	      	dz-=origin->z*4;
	      	}
	      else if(key=='w')
	      	{
	      	dx+=origin->x*4;
	      	dy+=origin->y*4;
	      	dz+=origin->z*4;
	      	}
	      else if(key=='a')//Pan Left
    		{
        	dx-=cross->x*4;
         dy-=cross->y*4;
         dz-=cross->z*4;
			}
         else if(key=='d')//Pan Right
    		{
        	dx+=cross->x*4;
        	dy+=cross->y*4;
        	dz+=cross->z*4;
        	}
    delete origin;
    delete cross;
    delete normal;
	 }
	 
}

void glutWidget::mouseMotion(int posx, int posy) {
    float deltax=posx-xcurr;
    float deltay=posy-ycurr;
    if(deltax>0)
        tau+=.02;
    else if(deltax<0)
        tau-=.02;
    if(deltay>0)
        phi+=.02;
    else if(deltay<0)
        phi-=.02;
    xcurr+=deltax;
    ycurr+=deltay;

   
    float r = sqrt(x*x+y*y+z*z);
    
    float rprime = r * cos(phi);
    if(r*sin(phi)<4&&freemode==0)
    	{
    	glutPostRedisplay();
    	if(deltay<0)
    		phi+=.02;
      else if(deltay>0)
      	phi-=.02;
      return;
    	}
    x = rprime * cos(tau);
    y = r*sin(phi);
    z = rprime * sin(tau);
    if(phi>2*M_PI||phi<-2*M_PI)

        {
        phi=0;
        }
    if((phi>M_PI/2&&phi<M_PI*3/2)||(phi<-M_PI/2&&phi>M_PI*-3/2))
        {
        flip=-1;
        }
    else
        {
        flip=1;
        }  
          glutPostRedisplay();  
                
}
void glutWidget::mouseButton(int button, int state, int xloc, int yloc) {
        if(button == GLUT_LEFT_BUTTON) {
            if(state == GLUT_DOWN) {
                xcurr=xloc;
                ycurr=yloc;
           //      std::cout<<"x:"<<x<<" y:"<<y<<std::endl;//<<" z:"<<z<<std::endl;
            }
        }
}

/*
    Forces program to stop, cleans up, and exits
 */
void glutWidget::stop()
{
    //clean up shaders
    glDetachShader(m_program,m_vertexsh);
	glDetachShader(m_program,m_fragmentsh);
    
    glDeleteProgram(m_program);
	glDeleteShader(m_vertexsh);
	glDeleteShader(m_fragmentsh);
    
    exit(0);
}

/*
    Reads in and compiles shader objects
 */
void glutWidget::makeShaders()
{
    m_program = glCreateProgram();
	
	char *shadercode = readShader("shaders/vertexshader.vert");	
    m_vertexsh = glCreateShader(GL_VERTEX_SHADER_ARB);
    glShaderSource(m_vertexsh, 1, (const GLcharARB **)&shadercode,NULL);
    delete[] shadercode;
    glCompileShader(m_vertexsh);
    printInfoLog(m_vertexsh);
    
    
	shadercode = readShader("shaders/fragmentshader.frag");
    m_fragmentsh = glCreateShader(GL_FRAGMENT_SHADER_ARB);
	glShaderSource(m_fragmentsh, 1, (const GLcharARB **)&shadercode,NULL);
	delete[] shadercode;
	glCompileShader(m_fragmentsh);
	printInfoLog(m_fragmentsh);
    
	glAttachShader(m_program,m_vertexsh);
	glAttachShader(m_program,m_fragmentsh);

	glLinkProgram(m_program);
	printInfoLog(m_program);
}


    
void glutWidget::normalize(Point* p)
    {
        float length = p->x*p->x+p->y*p->y+p->z*p->z;
        length = sqrt(length);
        p->x = p->x / length;
        p->y = p->y / length;
        p->z = p->z / length;
    }

Point* glutWidget::crossproduct(Point p1, Point p2)
    {
    Point* output= new Point(0,0,0);
    output->x = p1.y*p2.z - p1.z*p2.y;
    output->y = p1.z*p2.x - p1.x*p2.z;
    output->z = p1.x*p2.y - p1.y*p2.x;
    return output;
    }
    
/*
 Starts the main loop
 */
void glutWidget::run()
{
    glutMainLoop();
}

void glutWidget::update(int value)
{
    frame++;
   // std::cout<<frame<<std::endl;
	 if((frame+340)%640<50)
	 	{
	 	rotatey-=1.8;
	 	}
	 if(frame%640<50)
	 	{
	 	rotatey-=1.8;
	 	}
	 if((frame+430)%440<50)
	 	rotate2y-=1.8;
	 if((frame+310)%440<50)
	 	rotate2y-=1.8;
	 transz-=2*cos(rotatey*M_PI/180);
	 transx-=2*sin(rotatey*M_PI/180);
	 trans2z-=4*cos(rotate2y*M_PI/180);
	 trans2x-=4*sin(rotate2y*M_PI/180);
	 //std::cout<<transx<<std::endl;
	 //std::cout<<transz<<std::endl;
    glutPostRedisplay(); //marks window for redrawing
    glutTimerFunc(20,update,0);
    
}


/*
    Called whenever no user input given
 */
void glutWidget::update()
{
    m_frame++;
    glutPostRedisplay(); //marks window for redrawing
}
