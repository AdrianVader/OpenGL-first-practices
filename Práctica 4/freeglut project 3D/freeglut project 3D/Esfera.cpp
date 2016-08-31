
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include "Esfera.h"



void Esfera::draw(){

	// Color.
	glColor3f(Esfera::_r, Esfera::_g, Esfera::_b);

	//Colocar el objeto.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(*Esfera::_tAf._m);

	gluQuadricDrawStyle(Esfera::_obj, GLU_FILL);//GLU_POINT GLU_LINE GLU_FILL
	// gluSphere(q, radius, slices, stacks);
	gluSphere(Esfera::_obj, Esfera::_radio, 500, 500);

	glPopMatrix();

}

Esfera::Esfera(const GLdouble &rad, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &trasX, const GLdouble &trasY, const GLdouble &trasZ){

	Esfera::_obj = gluNewQuadric();
	Esfera::_radio = rad;

	Esfera::_r = r;
	Esfera::_g = g;
	Esfera::_b = b;

	Esfera::_tAf.trasladar(PV3D(trasX, trasY, trasZ, 0));

}

Esfera::~Esfera(void){}
