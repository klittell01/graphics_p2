#include "MyCam.h"
#include "math.h"
#include <iostream>
#include "windows.h"
SF3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z)
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}
SF3dVector AddF3dVectors(SF3dVector* u, SF3dVector* v)
{
	SF3dVector result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}
void AddF3dVectorToVector(SF3dVector * Dst, SF3dVector * V2)
{
	Dst->x += V2->x;
	Dst->y += V2->y;
	Dst->z += V2->z;
}


/***************************************************************************************/

MyCamera::MyCamera()
{
	// start at 100,100,100
	Position = F3dVector(100.0, 100.0, 100.0);
	// looking at 0,0,0
	ViewDir = F3dVector(0.0, 0.0, 0.0);
	ViewDirChanged = false;
}

void MyCamera::GetViewDir(void)
{
	SF3dVector Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos((rotY + 90.0) * (3.1415/180));
	Step1.z = -sin((rotY + 90.0) * (3.1415/180));
	//Rotate around X-axis:
	double cosX = cos(rotX * (3.1415 / 180));
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(rotX * (3.1415/180));
	//Rotation around Z-axis not yet implemented, so:
	ViewDir = Step2;
}

void MyCamera::RotY(GLfloat Angle)
{
	rotY += Angle;
	ViewDirChanged = true;
}

void MyCamera::RotX(GLfloat Angle)
{
	rotX += Angle;
	ViewDirChanged = true;
}

void MyCamera::Render(void)
{
	glRotatef(-rotX, 1.0, 0.0, 0.0);
	glRotatef(-rotY, 0.0, 1.0, 0.0);
	glRotatef(-rotZ, 0.0, 0.0, 1.0);
	glTranslatef(-Position.x, -Position.y, -Position.z);
}

void MyCamera::MoveForwards(GLfloat Distance)
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.x = ViewDir.x * -Distance;
	MoveVector.y = ViewDir.y * -Distance;
	MoveVector.z = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector);
}

void MyCamera::StrafeRight(GLfloat Distance)
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.z = -ViewDir.x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector);
}