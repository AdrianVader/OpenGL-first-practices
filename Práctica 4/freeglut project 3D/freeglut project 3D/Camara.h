
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>


#include "PV3D.h"


using namespace std;



class Camara
{

public:

	// Eye, punto donde se encuentra la cámara.
	PV3D _eye;

	// punto al que mira la cámara.
	PV3D _look;

	// Orientación de la cámara.
	PV3D _up;

	// U, V, N. Sistema de coordenadas de la cámara
	PV3D _u, _v, _n;

	// Left y right son coordenadas en el eje U
	// Bottom y top son coordenadas en el eje V
	// Near es la distancia al plano cercano
	// Far es la distancia al plano lejano
	// Define la caja de zapatos y la pirámide
	// Fovy es la apertura en el eje V
	// Aspect es la proporción de las dimensiones del plano cercano y del lejano
	GLdouble left, right, top, bottom, nea, fa, fovy, aspect;

	bool orthoMode;



	void recorridoEje(const int &x, const int &y, const int &z);

	void giraX();
	void giraY();
	void giraZ();

	void roll(int signo);
	void yaw(int signo);
	void pitch(int signo);

	//Coloca la cámara en un punto
	//Cambia las coordenadas de eye (mueve la cámara) y de U
	void set(const GLdouble &xE, const GLdouble &yE, const GLdouble &zE, const GLdouble &xU, const GLdouble &yU, const GLdouble &zU);

	void changePerspective();

	void actualizaNUV();


	Camara(const GLdouble &eyeX, const GLdouble &eyeY, const GLdouble &eyeZ, const GLdouble &lookX, const GLdouble &lookY, const GLdouble &lookZ, const GLdouble &upX, const GLdouble &upY, const GLdouble &upZ, const GLdouble &xLeft, const GLdouble &xRight, const GLdouble &yTop, const GLdouble &yBot, const GLdouble &n, const GLdouble &f, const GLdouble &fov, const GLdouble &asp);

	Camara(void);

	~Camara(void);

};