
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include "Disco.h"




void Disco::draw(){

	// Color.
	glColor3f(Disco::_r, Disco::_g, Disco::_b);

	//Colocar el objeto.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(*Disco::_tAf._m);

	gluQuadricDrawStyle(Disco::_obj, GLU_FILL);//GLU_POINT GLU_LINE GLU_FILL
	gluDisk(Disco::_obj, Disco::_radio, Disco::_radioGrande, 500, 500);

	glPopMatrix();

}

Disco::Disco(const GLdouble &rad, const GLdouble &radGrande, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &x, const GLdouble &y, const GLdouble &z){

	Disco::_obj = gluNewQuadric();
	Disco::_radio = rad;
	Disco::_radioGrande = radGrande;

	Disco::_r = r;
	Disco::_g = g;
	Disco::_b = b;

	Disco::_tAf.trasladar(PV3D(x, y, z, 0));

}

Disco::~Disco(void){}
