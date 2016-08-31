
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


#include "Objeto3D.h"



using namespace std;



class ObjetoCuadrico : public Objeto3D
{

public:
	
	GLUquadricObj* _obj;

	GLdouble _radio;


	virtual void draw() = 0;

	ObjetoCuadrico(void);

	~ObjetoCuadrico(void);

};