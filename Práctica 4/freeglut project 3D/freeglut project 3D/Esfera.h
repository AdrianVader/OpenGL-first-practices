
/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
*/


#pragma once



#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>


#include "ObjetoCuadrico.h"



using namespace std;



class Esfera : public ObjetoCuadrico
{

public:

	void draw();

	Esfera(const GLdouble &rad, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &trasX, const GLdouble &trasY, const GLdouble &trasZ);

	~Esfera(void);

};