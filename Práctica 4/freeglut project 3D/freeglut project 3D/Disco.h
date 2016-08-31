
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


#include "ObjetoCuadrico.h"



using namespace std;



class Disco : public ObjetoCuadrico
{

public:

	GLdouble _radioGrande;


	void draw();

	Disco(const GLdouble &rad, const GLdouble &radGrande, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &x, const GLdouble &y, const GLdouble &z);

	~Disco(void);

};