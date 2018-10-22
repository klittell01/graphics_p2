#include <gl\glut.h>		// Need to include it here because the GL* types are required


/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3dVector  //Float 3d-vect, normally used
{
	GLfloat x, y, z;
};
struct SF2dVector
{
	GLfloat x, y;
};

class MyCamera
{
private:
	SF3dVector Position;
	SF3dVector ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat rotX, rotY, rotZ = 0;
	void GetViewDir(void);
public:
	MyCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render(void);	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void RotX(GLfloat Angle);
	void RotY(GLfloat Angle);
	void RotZ(GLfloat Angle);
	void RotXYZ(SF3dVector Angles);
	void MoveForwards(GLfloat Distance);
	void StrafeRight(GLfloat Distance);
};


SF3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z);
SF3dVector AddF3dVectors(SF3dVector * u, SF3dVector * v);
void AddF3dVectorToVector(SF3dVector * Dst, SF3dVector * V2);
