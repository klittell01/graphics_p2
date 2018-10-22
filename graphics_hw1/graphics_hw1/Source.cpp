#define _CRT_SECURE_NO_WARNINGS
#include <string>

#include <iostream>
#include <istream>
#include <sstream>
#include <iterator> 

#include <fstream>

#include <strstream>

#include <vector>
//#include <glm/vec3.hpp> // glm::vec3

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

int size = 1024, pos;
int c;
char *buffer = (char *)malloc(1024);
float angle = 0.0f;
float myX = 0;
float myY = 0;
float myZ = 0;
float lx = 0.0f;
float lz = -0.1f;
float pi = 3.1415;
float yawL, yawR;
float roll = 0.1f;
int thisVert = 0;
int thisNorm = 0;
float verts[4096];
float norms[4096];

MyCam myCam;
//
//public void pan(float turnSpeed)
//{
//	totalPan += turnSpeed;
//
//	updateOrientation();
//}
//
//public void tilt(float turnSpeed)
//{
//	totalTilt += turnSpeed;
//
//	updateOrientation();
//}
//
//private void updateOrientation()
//{
//	float afterTiltX = 0.0f; // Not used. Only to make things clearer
//	float afterTiltY = (float)Math.sin(totalTilt));
//	float afterTiltZ = (float)Math.cos(totalTilt));
//
//	float vecX = (float)Math.sin(totalPan) * afterTiltZ;
//	float vecY = afterTiltY;
//	float vecZ = (float)Math.cos(totalPan) * afterTiltZ;
//
//	center = eye + vecmath.vector(vecX, vecY, vecZ);
//}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< display obj of revolution >>>>>>>>>>>>>>>>>>>>>>

void displayObjOfRev(void)

{
	Mesh * M;
	M = new Mesh();

	glMatrixMode(GL_PROJECTION); // set the view volume shape

	glLoadIdentity();

	gluPerspective(45, 1.333, .5f, 500);
	glTranslatef(myX, myY, myZ);
	glRotatef(angle, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW); // position and aim the camera

	glLoadIdentity();
	
	gluLookAt(100, 100, 100, 0, 0, 0, 0.0, 1.0, 0.0);




	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1, 0, 0); // draw black lines
	glScalef(.12, .12, .12);

	glBegin(GL_LINE_LOOP);
	for (int j = 0; j < thisVert; j += 3) {
		glVertex3d(verts[j] * 50, verts[j + 1] * 50, verts[j + 2] * 50);
		glNormal3f(norms[j] , norms[j + 1] , norms[j + 2] );
	}
	glEnd();
	glPushMatrix();
	glTranslated(100, 15, 0.5);
	M->makeSurfaceMesh();
	M->draw();
	glPopMatrix();

	glPushMatrix();

	glTranslated(-80.5, 10.5, 0.5);

	glutWireCube(25.0);

	glPopMatrix();	

	glFlush();
}

void myIdleFunction() {
	printf("this my roll1: %d\n", roll);
	roll = roll + 0.5f;
	printf("this my roll2: %d\n", roll);
	glMatrixMode(GL_MODELVIEW);
	glRotated(roll, 0.0, 0.0, 1.0);
	displayObjOfRev();
}


void pilotView (double planex, double planey, double planez,
	double roll, double pitch, double heading)
{
	glMatrixMode(GL_MODELVIEW);
	glRotated(roll, 0.0, 0.0, 1.0);
	glRotated(pitch, 0.0, 1.0, 0.0);
	glRotated(heading, 1.0, 0.0, 0.0);
	glTranslated(-planex, -planey, -planez);
}

void initLighting() {

	Mesh * tmp;
	tmp = new Mesh();
	tmp->makeSurfaceMesh2();
	glEnable(GL_LIGHTING);

	// set up light colors (ambient, diffuse, specular)

	GLfloat lightKa[] = { 1.2f, 0.0f, 0.0f, 1.0f };  // ambient light
	GLfloat lightKd[] = { 1.7f, 0.0f, 0.0f, 1.0f };  // diffuse light
	GLfloat lightKs[] = { 1, 0, 0, 1 };           // specular light

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	// position the light
	float lightPos[4] = { 0, 10, -20, 1 }; // positional light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration

	//gluLookAt(100, 100, 100, 0, 0, 0, 0.0, 1.0, 0.0);

}

void camLook(unsigned char key, int x, int y) {	
	float fraction = 0.1f;

	switch (key) {
		case '4': // strafe left
			angle -= 0.1f;
			myIdleFunction();
			//displayObjOfRev();
			//lx = sin(angle);
			//lz = -cos(angle);
			break;
		case '6': // strafe right
			angle += 0.1f;
			//lx = sin(angle);
			//lz = -cos(angle);
			break;
		case '5': // move forward
			myZ = myZ + .5;
			//myX += lx * fraction;
			//myZ += lz * fraction;
			break;
		case '1': // move backward
			myZ = myZ - .5;
			//myX -= lx * fraction;
			//myZ -= lz * fraction;
			break;
		case '8': // move up
			myY = myY - .5;
			//myX += lx * fraction;
			//myZ += lz * fraction;
			break;
		case '2': // move backward
			myY = myY + .5;
			//myX -= lx * fraction;
			//myZ -= lz * fraction;
			break;

			// more advanced movements //

		case 'A': // yaw left
			roll = roll + .5;
			glMatrixMode(GL_MODELVIEW);
			glRotated(roll, 0.0, 0.0, 1.0);
	}
}




//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void main(int argc, char **argv){

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(640, 480);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("Graphics Project 2");


	string token;
	string delim = " ";
	int size = 1024, pos;
	int c;
	char *buffer = (char *)malloc(size);
	ifstream infile("myobj.obj", ios::in);
	char myLine[1024];
	//FILE * objFile;
	//objFile = fopen("myobj.obj", "r");


	while (infile) {
		infile.getline(myLine, 1024);
		if (myLine[0] == 'v' && myLine[1] == 'n') {
			std::istringstream iss(myLine);
			vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
			for (int i = 0; i < 3; i++){
				norms[thisNorm + i] = stof(results[i + 1]);
			}
		}
		else if (myLine[0] == 'v') {
			std::istringstream iss(myLine);
			vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
			// put the points into a our point array
			for (int i = 0; i < 3; i++) {
				verts[thisVert + i] = stof(results[i + 1]);
			}
		}
		thisVert += 3;
	}

	glutKeyboardFunc(camLook);
	glutDisplayFunc(displayObjOfRev);
	//glutIdleFunc(myIdleFunction);
	glEnable(GL_DEPTH_TEST);
	initLighting();
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	glViewport(0, 0, 640, 480);

	glutMainLoop();

}


