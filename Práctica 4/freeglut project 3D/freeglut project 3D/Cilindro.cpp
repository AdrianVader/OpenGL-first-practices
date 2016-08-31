
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include "Cilindro.h"



void Cilindro::draw(){

	// Color.
	glColor3f(Cilindro::_r, Cilindro::_g, Cilindro::_b);

	//Colocar el objeto.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(*Cilindro::_tAf._m);

	gluQuadricDrawStyle(Cilindro::_obj, GLU_FILL);// GLU_POINT GLU_LINE GLU_FILL
	gluCylinder(Cilindro::_obj, Cilindro::_radio, Cilindro::_radioSuperior, Cilindro::_altura, 500, 500);

	glPopMatrix();

}

Cilindro::Cilindro(const GLdouble &radioInf, const GLdouble &radioSup, const GLdouble &altura, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &x, const GLdouble &y, const GLdouble &z){
	
	Cilindro::_obj = gluNewQuadric();
	Cilindro::_radio = radioInf;
	Cilindro::_radioSuperior = radioSup ;
	Cilindro::_altura = altura;

	Cilindro::_r = r;
	Cilindro::_g = g;
	Cilindro::_b = b;

	Cilindro::_tAf.trasladar(PV3D(x, y, z, 0));

}

Cilindro::Cilindro(const GLdouble &radioInf, const GLdouble &radioSup, const GLdouble &altura, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &x, const GLdouble &y, const GLdouble &z, const GLdouble &rot, const GLdouble &xRot, const GLdouble &yRot, const GLdouble &zRot){

	Cilindro::_obj = gluNewQuadric();
	Cilindro::_radio = radioInf;
	Cilindro::_radioSuperior = radioSup ;
	Cilindro::_altura = altura;

	Cilindro::_r = r;
	Cilindro::_g = g;
	Cilindro::_b = b;

	Cilindro::_tAf.trasladar(PV3D(x, y, z, 0));
	Cilindro::_tAf.rotar(rot, xRot, yRot, zRot);

}

Cilindro::~Cilindro(void){}
