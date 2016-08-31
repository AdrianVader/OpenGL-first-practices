
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



class TAfin
{

public:

	GLfloat _m[4][4];


	void escalar(const PV3D &v);

	void trasladar(const PV3D &v);

	void rotar(const GLdouble &grados, const GLdouble &x, const GLdouble &y, const GLdouble &z);

	void postmultiplicar(const GLfloat m[4][4]);

	TAfin(void);

	~TAfin(void);

};