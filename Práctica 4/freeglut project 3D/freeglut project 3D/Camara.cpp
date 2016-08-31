
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>



#include <math.h>

#include "Camara.h"



void Camara::recorridoEje(const int &x, const int &y, const int &z){

	if(x != 0){
		Camara::_eye._x += x;

	}else if(y != 0){
		Camara::_eye._y += y;
		
	}else{
		Camara::_eye._z += z;

	}
	
	glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
	glLoadIdentity();
	gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);

	Camara::actualizaNUV();

}


void Camara::giraX(){

	const GLdouble RAD = 0.0174532925;
	GLdouble alpha = 360/36;

	GLdouble radius = sqrt(pow(Camara::_eye._y, 2) + pow(Camara::_eye._z, 2));
	if(radius != 0){
		GLdouble mod = Camara::_eye._z/radius;
		GLdouble beta = acos(mod)/RAD;

		if(Camara::_eye._y < 0)
			beta = -beta;

		beta -= alpha;

		Camara::_eye = PV3D(Camara::_eye._x, sin(beta*RAD)*radius, cos(beta*RAD)*radius, 1);
	
		glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
		glLoadIdentity();
		gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);
	
		Camara::actualizaNUV();
	}

}

void Camara::giraY(){

	const GLdouble RAD = 0.0174532925;
	GLdouble alpha = 360/36;

	GLdouble radius = sqrt(pow(Camara::_eye._x, 2) + pow(Camara::_eye._z, 2));
	if(radius != 0){
		GLdouble mod = Camara::_eye._x/radius;
		GLdouble beta = acos(mod)/RAD;

		if(Camara::_eye._z < 0)
			beta = -beta;

		beta += alpha;

		Camara::_eye = PV3D(cos(beta*RAD)*radius, Camara::_eye._y, sin(beta*RAD)*radius, 1);

		glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
		glLoadIdentity();
		gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);
	
		Camara::actualizaNUV();
	}

}

void Camara::giraZ(){

	const GLdouble RAD = 0.0174532925;
	GLdouble alpha = 360/36;

	GLdouble radius = sqrt(pow(Camara::_eye._x, 2) + pow(Camara::_eye._y, 2));
	if(radius != 0){
		GLdouble mod = Camara::_eye._x/radius;
		GLdouble beta = acos(mod)/RAD;

		if(Camara::_eye._y < 0)
			beta = -beta;

		beta += alpha;

		Camara::_eye = PV3D(cos(beta*RAD)*radius, sin(beta*RAD)*radius, Camara::_eye._z, 1);

		glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
		glLoadIdentity();
		gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);
	
		Camara::actualizaNUV();
	}

}


// Rotación en base a n
void Camara::roll(int signo){

	GLfloat m [4][4];
	
	const GLdouble RAD = 0.0174532925;

	GLdouble alpha = 3*RAD; // giro de 3 grados

	if(signo < 0){
		alpha = -alpha;
	}

	Camara::_v = PV3D(Camara::_v._x*cos(alpha) + Camara::_n.productoV(Camara::_v)._x*sin(alpha) + Camara::_n._x*(Camara::_n.productoE(Camara::_v)*(1-cos(alpha))),
						Camara::_v._y*cos(alpha) + Camara::_n.productoV(Camara::_v)._y*sin(alpha) + Camara::_n._y*(Camara::_n.productoE(Camara::_v)*(1-cos(alpha))), 
						Camara::_v._z*cos(alpha) + Camara::_n.productoV(Camara::_v)._z*sin(alpha) + Camara::_n._z*(Camara::_n.productoE(Camara::_v)*(1-cos(alpha))),
						0);

	Camara::_u = PV3D(Camara::_u._x*cos(alpha) + Camara::_n.productoV(Camara::_u)._x*sin(alpha) + Camara::_n._x*(Camara::_n.productoE(Camara::_u)*(1-cos(alpha))),
						Camara::_u._y*cos(alpha) + Camara::_n.productoV(Camara::_u)._y*sin(alpha) + Camara::_n._y*(Camara::_n.productoE(Camara::_u)*(1-cos(alpha))), 
						Camara::_u._z*cos(alpha) + Camara::_n.productoV(Camara::_u)._z*sin(alpha) + Camara::_n._z*(Camara::_n.productoE(Camara::_u)*(1-cos(alpha))),
						0);

	m[0][0] = Camara::_u._x;
	m[0][1] = Camara::_v._x;
	m[0][2] = Camara::_n._x;
	m[0][3] = 0;

	m[1][0] = Camara::_u._y;
	m[1][1] = Camara::_v._y;
	m[1][2] = Camara::_n._y;
	m[1][3] = 0;

	m[2][0] = Camara::_u._z;
	m[2][1] = Camara::_v._z;
	m[2][2] = Camara::_n._z;
	m[2][3] = 0;

	m[3][0] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_u);
	m[3][1] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_v);
	m[3][2] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_n);
	m[3][3] = 1;


	glLoadMatrixf(*m);

}

// Rotación en base a v
void Camara::yaw(int signo){

	GLfloat m [4][4];
	
	const GLdouble RAD = 0.0174532925;

	GLdouble alpha = 3*RAD; // giro de 3 grados

	if(signo < 0){
		alpha = -alpha;
	}

	Camara::_n = PV3D(Camara::_n._x*cos(alpha) + Camara::_v.productoV(Camara::_n)._x*sin(alpha) + Camara::_v._x*(Camara::_v.productoE(Camara::_n)*(1-cos(alpha))),
						Camara::_n._y*cos(alpha) + Camara::_v.productoV(Camara::_n)._y*sin(alpha) + Camara::_v._y*(Camara::_v.productoE(Camara::_n)*(1-cos(alpha))), 
						Camara::_n._z*cos(alpha) + Camara::_v.productoV(Camara::_n)._z*sin(alpha) + Camara::_v._z*(Camara::_v.productoE(Camara::_n)*(1-cos(alpha))),
						0);

	Camara::_u = PV3D(Camara::_u._x*cos(alpha) + Camara::_v.productoV(Camara::_u)._x*sin(alpha) + Camara::_v._x*(Camara::_v.productoE(Camara::_u)*(1-cos(alpha))),
						Camara::_u._y*cos(alpha) + Camara::_v.productoV(Camara::_u)._y*sin(alpha) + Camara::_v._y*(Camara::_v.productoE(Camara::_u)*(1-cos(alpha))), 
						Camara::_u._z*cos(alpha) + Camara::_v.productoV(Camara::_u)._z*sin(alpha) + Camara::_v._z*(Camara::_v.productoE(Camara::_u)*(1-cos(alpha))),
						0);

	m[0][0] = Camara::_u._x;
	m[0][1] = Camara::_v._x;
	m[0][2] = Camara::_n._x;
	m[0][3] = 0;

	m[1][0] = Camara::_u._y;
	m[1][1] = Camara::_v._y;
	m[1][2] = Camara::_n._y;
	m[1][3] = 0;

	m[2][0] = Camara::_u._z;
	m[2][1] = Camara::_v._z;
	m[2][2] = Camara::_n._z;
	m[2][3] = 0;

	m[3][0] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_u);
	m[3][1] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_v);
	m[3][2] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_n);
	m[3][3] = 1;


	glLoadMatrixf(*m);

}

// Rotación en base a u
void Camara::pitch(int signo){

	GLfloat m [4][4];
	
	const GLdouble RAD = 0.0174532925;

	GLdouble alpha = 3*RAD; // giro de 3 grados

	if(signo < 0){
		alpha = -alpha;
	}

	Camara::_v = PV3D(Camara::_v._x*cos(alpha) + Camara::_u.productoV(Camara::_v)._x*sin(alpha) + Camara::_u._x*(Camara::_u.productoE(Camara::_v)*(1-cos(alpha))),
						Camara::_v._y*cos(alpha) + Camara::_u.productoV(Camara::_v)._y*sin(alpha) + Camara::_u._y*(Camara::_u.productoE(Camara::_v)*(1-cos(alpha))), 
						Camara::_v._z*cos(alpha) + Camara::_u.productoV(Camara::_v)._z*sin(alpha) + Camara::_u._z*(Camara::_u.productoE(Camara::_v)*(1-cos(alpha))),
						0);

	Camara::_n = PV3D(Camara::_n._x*cos(alpha) + Camara::_u.productoV(Camara::_n)._x*sin(alpha) + Camara::_u._x*(Camara::_u.productoE(Camara::_n)*(1-cos(alpha))),
						Camara::_n._y*cos(alpha) + Camara::_u.productoV(Camara::_n)._y*sin(alpha) + Camara::_u._y*(Camara::_u.productoE(Camara::_n)*(1-cos(alpha))), 
						Camara::_n._z*cos(alpha) + Camara::_u.productoV(Camara::_n)._z*sin(alpha) + Camara::_u._z*(Camara::_u.productoE(Camara::_n)*(1-cos(alpha))),
						0);

	m[0][0] = Camara::_u._x;
	m[0][1] = Camara::_v._x;
	m[0][2] = Camara::_n._x;
	m[0][3] = 0;

	m[1][0] = Camara::_u._y;
	m[1][1] = Camara::_v._y;
	m[1][2] = Camara::_n._y;
	m[1][3] = 0;

	m[2][0] = Camara::_u._z;
	m[2][1] = Camara::_v._z;
	m[2][2] = Camara::_n._z;
	m[2][3] = 0;

	m[3][0] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_u);
	m[3][1] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_v);
	m[3][2] = PV3D(-Camara::_eye._x, -Camara::_eye._y, -Camara::_eye._z, 1).productoE(Camara::_n);
	m[3][3] = 1;


	glLoadMatrixf(*m);

}


void Camara::set(const GLdouble &xE, const GLdouble &yE, const GLdouble &zE, const GLdouble &xU, const GLdouble &yU, const GLdouble &zU){

	Camara::_eye._x = xE;
	Camara::_eye._y = yE;
	Camara::_eye._z = zE;

	Camara::_up._x = xU;
	Camara::_up._y = yU;
	Camara::_up._z = zU;

	glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
	glLoadIdentity();
	gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);
	
	Camara::actualizaNUV();

}


void Camara::changePerspective(){

	//Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
	if(Camara::orthoMode){
		glOrtho(Camara::left, Camara::right, Camara::bottom, Camara::top, Camara::nea, Camara::fa);
	}else{
		gluPerspective(Camara::fovy, Camara::aspect, Camara::nea, Camara::fa);
	}

	glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
	glLoadIdentity();
	gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);

}

void Camara::actualizaNUV(){

	Camara::_n = PV3D(Camara::_eye._x-Camara::_look._x, Camara::_eye._y-Camara::_look._y, Camara::_eye._z-Camara::_look._z, 0).normalize();
	Camara::_u = PV3D(Camara::_up.productoV(Camara::_n)).normalize();
	Camara::_v = Camara::_n.productoV(Camara::_u);

}

Camara::Camara(const GLdouble &eyeX, const GLdouble &eyeY, const GLdouble &eyeZ, const GLdouble &lookX, const GLdouble &lookY, const GLdouble &lookZ, const GLdouble &upX, const GLdouble &upY, const GLdouble &upZ, const GLdouble &xLeft, const GLdouble &xRight, const GLdouble &yTop, const GLdouble &yBot, const GLdouble &n, const GLdouble &f, const GLdouble &fov, const GLdouble &asp){

	Camara::_eye = PV3D(eyeX, eyeY, eyeZ, 1);
	Camara::_look = PV3D(lookX, lookY, lookZ, 1);
	Camara::_up = PV3D(upX, upY, upZ, 0);

	Camara::actualizaNUV();

	glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
	glLoadIdentity();
	gluLookAt(Camara::_eye._x, Camara::_eye._y, Camara::_eye._z, Camara::_look._x, Camara::_look._y, Camara::_look._z, Camara::_up._x, Camara::_up._y, Camara::_up._z);

	Camara::left = xLeft;
	Camara::right = xRight;
	Camara::top = yTop;
	Camara::bottom = yBot;
	Camara::nea = n;
	Camara::fa = f;
	Camara::fovy = fov;
	Camara::aspect = asp;

	Camara::orthoMode = true;

	//Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
	if(Camara::orthoMode){
		glOrtho(Camara::left, Camara::right, Camara::bottom, Camara::top, Camara::nea, Camara::fa);
	}else{
		gluPerspective(Camara::fovy, Camara::aspect, Camara::nea, Camara::fa);
	}

}

Camara::Camara(void){}

Camara::~Camara(void){}