#include "Camera.h"

void PrintN(float& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}


// setModelViewMatrix used in the book "Computer Graphics using OpenGL" Hill/Kelley page 336
void Camera::setModelViewMatrix() {
	float m[16];
	Vector eVec(eye.x, eye.y, eye.z);

	m[0] = u.x;
	m[1] = v.x;
	m[2] = n.x;
	m[3] = 0;
	m[4] = u.y;
	m[5] = v.y;
	m[6] = n.y;
	m[7] = 0;
	m[8] = u.z;
	m[9] = v.z;
	m[10] = n.z;
	m[11] = 0;
	m[12] = -eVec.dot(u);
	m[13] = -eVec.dot(v);
	m[14] = -eVec.dot(n);
	m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::set(float ex, float ey, float ez, float lx, float ly, float lz, float ux, float uy, float uz) {
	Point e(ex, ey, ez);
	Point l(lx, ly, lz);
	Vector y(ux, uy, uz);
	set(e, l, y);
}

// set used in the book "Computer Graphics using OpenGL" Hill/Kelley page 336
void Camera::set(Point& e, Point& l, Vector& y) {
	eye.set(e);
	look.set(l);
	up.set(y);
	n.set(e - l);
	u.set(y.cross(n));
	n.normalize();
	u.normalize();
	v.set(n.cross(u));
	v.normalize();
	setModelViewMatrix();
}


// slide used in the book "Computer Graphics using OpenGL" Hill/Kelley page 337
// the book had typos that have been corrected here
// move camera and look point according to delta values
void Camera::slide(float delU, float delV, float delN) {
	float dx = delU * u.x + delV * v.x + delN * n.x;
	float dy = delU * u.y + delV * v.y + delN * n.y;
	float dz = delU * u.z + delV * v.z + delN * n.z;

	eye.x += dx;
	eye.y += dy;
	eye.z += dz;

	look.x += dx;
	look.y += dy;
	look.z += dz;

	setModelViewMatrix();
}

//Change camera to perspective or parallel
void Camera::setShape(float vAng, float asp, float nearD, float farD) {
	float degrees;
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);

	degrees = ((viewAngle / 2)*pi) / 180;
	H = nearDist * tan(degrees);
	W = H * aspect;

	printf("H:");
	PrintN(H);
	printf("\nW:");
	PrintN(W);
	printf("\n");
}


// roll used in the book "Computer Graphics using OpenGL" Hill/Kelley page 338
// rotate around n vector
void Camera::roll(float theta) {
	float cs = cos(pi / 180 * theta);
	float sn = sin(pi / 180 * theta);
	Vector t(u);
	u.set(cs*t.x + sn * v.x, cs*t.y + sn * v.y, cs*t.z + sn * v.z);
	v.set(-sn * t.x + cs * v.x, -sn * t.y + cs * v.y, -sn * t.z + cs * v.z);
	u.normalize();
	v.normalize();
	setModelViewMatrix();
}


// rotate camera around u vector
void Camera::pitch(float theta) {
	float cs = cos(pi / 180 * theta);
	float sn = sin(pi / 180 * theta);
	Vector t(v);
	//v.set( ....fill this in... );
	//n.set( ....fill this in... );
	v.normalize();
	n.normalize();
	setModelViewMatrix();
}

//rotate camera around v vector
void Camera::yaw(float theta) {
	float cs = cos(pi / 180 * theta);
	float sn = sin(pi / 180 * theta);
	Vector t(n);
	//n.set( ....fill this in...  );
	//u.set( ....fill this in...  );
	n.normalize();
	u.normalize();
	setModelViewMatrix();
}


// rotate camera around a fixed point such that the camera
// is always looking at that point (0, 0, 0);
void Camera::FocusedPitch(float theta) {
	//to be completed
}


// rotate camera around a fixed point such that the camera
// is always looking at that point (0, 0, 0);
void Camera::FocusedYaw(float theta) {
	//to be completed


}


void Camera::CenterFocus() {
	Point center;
	set(eye, center, up);
}


Vector Camera::GetC(int width, int height, int i, int j) {
	Vector c;

	c.set((n*(nearDist*-1)) + u * (W*((float(2 * i) / float(width)) - 1.0f)) + v * (H*((float(2 * j) / float(height)) - 1.0f)));
	//c.normalize();
	return c;
}

Point Camera::GetEye() {
	return eye;
}