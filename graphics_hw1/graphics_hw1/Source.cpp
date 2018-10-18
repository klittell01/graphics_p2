#include <string>

#include <iostream>

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

float angle = 0.0f;
float myX = 50;
float myY = 50;
float myZ = 50;
float lx = 0.0f;
float lz = -0.1f;

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

void displayObjOfRev(void)

{
	Mesh * M;
	M = new Mesh();

	glMatrixMode(GL_PROJECTION); // set the view volume shape

	glLoadIdentity();

	gluPerspective(45, 1.333, .5f, 150);

	glMatrixMode(GL_MODELVIEW); // position and aim the camera

	glLoadIdentity();

	gluLookAt(myX, myY, myZ, 0, 0, 0, 0.0, 1.0, 0.0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1, 0, 0); // draw black lines
	M->makeSurfaceMesh();
	M->draw();



	glFlush();

}

void initLighting() {

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

}

void camLook(int key, int x, int y) {	
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
			myX += lx * fraction;
			myZ += lz * fraction;
			break;
		case GLUT_KEY_DOWN:
			myX -= lx * fraction;
			myZ -= lz * fraction;
			break;
	}
}


//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void main(int argc, char **argv)

{
	//std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	//std::vector< vec3 > temp_vertices;
	//std::vector< vec2 > temp_uvs;
	//std::vector< vec3 > temp_normals;

	//FILE * file = fopen(path, "r");
	//if (file == NULL) {
	//	printf("Impossible to open the file !\n");
	//	return false;
	//}

	//while (1) {

	//	char lineHeader[128];
	//	// read the first word of the line
	//	int res = fscanf(file, "%s", lineHeader);
	//	if (res == EOF) {
	//		break; // EOF = End Of File. Quit the loop.
	//	}
	//	if (strcmp(lineHeader, "v") == 0) {
	//		glm::vec3 vertex;
	//		fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
	//		temp_vertices.push_back(vertex);
	//	}
	//	else if (strcmp(lineHeader, "vt") == 0) {
	//		glm::vec2 uv;
	//		fscanf(file, "%f %f\n", &uv.x, &uv.y);
	//		temp_uvs.push_back(uv);
	//	}
	//	else if (strcmp(lineHeader, "vn") == 0) {
	//		glm::vec3 normal;
	//		fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	//		temp_normals.push_back(normal);
	//	}
	//	else if (strcmp(lineHeader, "f") == 0) {
	//		std::string vertex1, vertex2, vertex3;
	//		unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	//		int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
	//		if (matches != 9) {
	//			printf("File can't be read by our simple parser : ( Try exporting with other options\n");
	//			return false;
	//		}
	//		vertexIndices.push_back(vertexIndex[0]);
	//		vertexIndices.push_back(vertexIndex[1]);
	//		vertexIndices.push_back(vertexIndex[2]);
	//		uvIndices.push_back(uvIndex[0]);
	//		uvIndices.push_back(uvIndex[1]);
	//		uvIndices.push_back(uvIndex[2]);
	//		normalIndices.push_back(normalIndex[0]);
	//		normalIndices.push_back(normalIndex[1]);
	//		normalIndices.push_back(normalIndex[2]);
	//	}
	//}
	//
	//// For each vertex of each triangle
	//for (unsigned int i = 0; i < vertexIndices.size(); i++) {
	//	unsigned int vertexIndex = vertexIndices[i];
	//	glm::vec3 vertex = temp_vertices[vertexIndex - 1];
	//	out_vertices.push_back(vertex);
	//}

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(640, 480);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("Graphics Project 2");

	glutSpecialFunc(camLook);
	glutDisplayFunc(displayObjOfRev);
	glutIdleFunc(displayObjOfRev);
	glEnable(GL_DEPTH_TEST);
	initLighting();
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	glViewport(0, 0, 640, 480);

	glutMainLoop();

}


