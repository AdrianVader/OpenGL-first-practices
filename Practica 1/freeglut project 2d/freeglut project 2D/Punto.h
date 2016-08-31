
/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
*/


#pragma once


#include<GL\freeglut.h>



using namespace std;


class Punto
{

public:

	GLdouble _x, _y;


	Punto(const GLdouble &x, const GLdouble &y);

	Punto();

	~Punto(void);

};

