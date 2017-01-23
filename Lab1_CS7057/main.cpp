#include <GL/freeglut.h>
#include "teapot.h"

double rotAngle = 10; // a global variable



/***************************************************************
 ** init function ***
 
 set up some default OpenGL values here

 ***************************************************************/

void init()
{
	glClearColor(0, 0, 0, 0); //background color
	glClearDepth(1.0);	//background depth value

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 1000);  //setup a perspective projection

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(						//set up camera
				0.0, 0.0, 5.0,		// eye position
				0.0, 0.0, 0.0,		// lookat position
				0.0, 1.0, 0.0		// up direction
				);


	glEnable(GL_DEPTH_TEST); //enable z-buffer hidden surface removal

	glEnable(GL_LIGHTING); //enable lighting
	glEnable(GL_LIGHT0); //enable
	
	float lpos[] = { 5, 5, 5, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	//glShadeModel(GL_FLAT); //flat shading
	glShadeModel(GL_SMOOTH); //smooth shading (default): enables Gouraud shading


}


/***************************************************************
 ** display callback function **
 - get's called each time application needs to redraw itself
 - most opengl work is done through this function
 ***************************************************************/


void display()
{
	glClear(
		GL_COLOR_BUFFER_BIT  //clear the frame buffer (set it to background color)
		| GL_DEPTH_BUFFER_BIT //clear the depth buffer for z-buffer hidden surface removal 
		);

	glPushMatrix(); // save current modelview matrix (mostly saves camera transform)
		
	//////////////////******* insert your openGL drawing code here ****** ///////////
	
	glRotated(rotAngle, 0, 1, 0); //rotate by rotAngle about y-axis


	
	glEnable(GL_COLOR_MATERIAL);	//instead of specifying material properties
	glColor3f(1, .1, .1);			//  we will use glColor to set the diffuse color

	glutSolidTeapot(1);

	////////////////////////////////////////////////////////////////

	glPopMatrix(); // retrieve modelview matrix
	glFlush(); //force OpenGL to render now;

	glutSwapBuffers(); // when using double buffering, need to swap front and back buffer
}


/*************************************************************
 ** keyboard callback function **

 *************************************************************/

void keyboard(unsigned char k, int x, int y)
{

	switch (k)
	{
	case 'a':
		rotAngle+=5; //changes a global variable ... this is later picked up by display
		break;
	case 'd':
		rotAngle-=5;  //changes a global variable ... this is later picked up by display
		break;
	}

	glutPostRedisplay(); //tell glut that the display callback should be called after this
}


/*************************************************************
 ** main ***
 where everything begins

*************************************************************/

void main()
{
	glutInitDisplayMode(	// initialize GLUT
			GLUT_DOUBLE		// request memory for 2 frame buffers for animation
			| GLUT_DEPTH	// request memory for z-buffer
			| GLUT_RGB		// set RGB color mode
			); 

	glutCreateWindow("GLUT Example 02");	// create a window
	glutDisplayFunc(display);				// set the display callback

	glutKeyboardFunc(keyboard);
	
	init();
	
	glutMainLoop();	// now let GLUT take care of everything
}
