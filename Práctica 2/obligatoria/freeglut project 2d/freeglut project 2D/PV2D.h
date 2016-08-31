
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


using namespace std;



class PV2D
{

public:

	GLdouble _x; // Point or vector in x's axis.

	GLdouble _y; // Point or vector in y's axis.


	PV2D(const GLdouble &x, const GLdouble &y);

	PV2D(void);

	~PV2D(void);

};
