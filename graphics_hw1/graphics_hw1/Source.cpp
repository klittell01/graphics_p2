
#include "GL/glut.h" //modify this for your environment
#include <math.h>
#include <stdio.h>


#include <string>

#include <iostream>

#include <fstream>

#include <strstream>
using namespace std;

#include <windows.h> //change if using xWindows

#include <assert.h>

#include <math.h>

#include <stdlib.h>

#include <gl/Gl.h>

#include <gl/Glu.h>

#include "GL/glut.h"

#include "Meshclass.h"



//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>

void axis(double length)

{ // draw a z-axis, with cone at end

	glPushMatrix();

	glBegin(GL_LINES);

	glVertex3d(0, 0, 0); glVertex3d(0, 0, length); // along the z-axis

	glEnd();

	glTranslated(0, 0, length - 0.2);

	glutWireCone(0.04, 0.2, 12, 9);

	glPopMatrix();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>

void displayWire(void)

{
	//Mesh * M;
	//M = new Mesh();

	//glMatrixMode(GL_PROJECTION); // set the view volume shape

	glLoadIdentity();

	//glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);

	glMatrixMode(GL_MODELVIEW); // position and aim the camera

	glLoadIdentity();

	//gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1, 0, 0); // draw black lines
	//M->makeSurfaceMesh();
	//M->draw();
}



// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;




void MyCube(GLfloat size, GLfloat segment_length) {
	glPolygonMode(GL_BACK, GL_NONE);
	glPolygonMode(GL_FRONT, GL_FILL);

	glPushMatrix(); {
		GLfloat myZ = 0.0;
		GLfloat newZ = segment_length;

		GLfloat y_offset = 0.0;
		GLfloat y_change = 0.00;

		int i = 0;
		int j = 0;
	//	for (j = 0; j < 20; j++) {
			glPushMatrix(); {
				glColor3f(0.51, 0.87, 0.15);
				glBegin(GL_QUADS); {
					for (i = 20; i >= 0; i--) {
						glVertex3i(0, 0, i);
						glVertex3i(0, 1 * size, i);
						glVertex3i(1 * size, 1 * size, i);
						glVertex3i(1 * size, 0, i);

						//GLfloat theta = i * 3.1415 / 180;
						//GLfloat x = radius * cos(theta);
						//GLfloat y = radius * sin(theta) + y_offset;

						//glVertex3f(x, y, z1);
						//glVertex3f(x, y, z2);
					}
	//			} 
				glEnd();
			} glPopMatrix();

			// attach the front of the next segment to the back of the previous
			myZ = newZ;
			newZ += segment_length;

			// make some other adjustments
			//y_offset += y_change;
		}
	} glPopMatrix();
}


void displayObjects(void)

{
	
	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	gluPerspective(45.0f, 640/480, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(x + 5, 5.0f, z + 5, 0, 0, 0, 0.0f, 1.0f, 0.0f);

	
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
     glColor3d(1,0,0); // draw black lines

	glDisable(GL_LIGHT0); 

	glPushMatrix();
	glTranslated(0, 1.5, -1); //lightPos
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glEnable(GL_LIGHT0);

	//MyCube(2.0f, 2.0f);
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	GLfloat amb[] = {0.6f, 0.6f, 0.6, 0.5f};  // ambient 
        GLfloat diff[] = {0.9f, 0.9f, 0.9, 0.5};  // diffuse 
        GLfloat spec[] = {1,1, 1, 1};           // specular

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 200.0);
   
	glPushMatrix();	
	glTranslated(0,1,0);
	glutSolidSphere(0.25, 10, 8);
	glPopMatrix();	

	
	
	GLfloat amb2[] = {1.0f, 0.0f, 0.0, 1.0f};  // ambient 
   	 GLfloat diff2[] = {1.0f, 0.0f, 0.0, 1.0};  // diffuse 

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb2);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff2);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);

	glPushMatrix();	
	glTranslated(-0.5,-0.2,0.2);
	glutSolidCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	
	GLfloat amb3[] = {0.6f, 0.6f, 1.0, 0.3f};  // ambient 
   	 GLfloat diff3[] = {0.9f, 0.9f, 1.0, 0.3};  // diffuse 
   
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb3);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff3);
   	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);
	glPushMatrix();

	glTranslated(-2,1,1);
	glutSolidTeapot(0.2); 
	glPopMatrix();

	GLfloat amb4[] = {0.6f, 1.0f, 0.6, 0.4f};  // ambient 
   	 GLfloat diff4[] = {0.9f, 1.0f, 0.9, 0.4};  // diffuse 
    
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb4);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff4);
   	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);

	glPushMatrix();
	glTranslated(1,1,1);
	glRotated(90.0, 1,0,0);
	glutSolidTorus(0.1, 0.3, 10,10);
	glPopMatrix();
		
	GLfloat amb5[] = {1.0f, 0.0f, 1.0, 0.5f};  // ambient 
   	 GLfloat diff5[] = {1.0f, 0.0f, 1.0, 0.5};  // diffuse 
    
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, amb5);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diff5);
   	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 7.0);

	glPushMatrix();
	glTranslated(1,1.5,1);
	glTranslated(1.0, 0 ,0); // dodecahedron at (1,0,0)
	glScaled(0.15, 0.15, 0.15);
	glutSolidDodecahedron();
	glPopMatrix();


	glFlush();
	glutSwapBuffers(); 

}


void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		printf("pushing up key");
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}



void initLighting(){

	glEnable(GL_LIGHTING);

   // set up light colors (ambient, diffuse, specular)

    GLfloat lightKa[] = {0.8f, 0.8f, 0.8f, 1.0f};  // ambient light
    GLfloat lightKd[] = {0.8f, 0.8f, 0.8f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {0.8f, 0.8f, 0.8f, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
	
    // position the light
    float lightPos[4] = {0, 1.5, -1,1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration

	



}



//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void main(int argc, char **argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );

	glutInitWindowSize(640,480);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("Materials and Lighting testbed");



	glutDisplayFunc(displayObjects);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	initLighting();
	glClearColor(1.0f, 0.25f, 1.0f,0.0f);  // background is white
	//glEnable(GL_FLAT);
    glShadeModel(GL_SMOOTH);
	glEnable(GL_SMOOTH);
	glViewport(0, 0, 640, 480);

	glutMainLoop();

}


