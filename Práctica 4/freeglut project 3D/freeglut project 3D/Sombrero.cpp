
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include "Sombrero.h"



void Sombrero::draw(){

	//Colocar el objeto.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(*Sombrero::_tAf._m);

	list<Objeto3D*>::iterator it = Sombrero::_objList.begin();
	while(it != Sombrero::_objList.end()){

		it._Ptr->_Myval->draw();

		it++;
	}

	glPopMatrix();

}

Sombrero::Sombrero(const GLdouble &x, const GLdouble &y, const GLdouble &z){

	Sombrero::_objList.push_back(new Cilindro(0.75, 0.75, 1.5, 0.5, 0.5, 0.5, 0, 0, 0));
	Sombrero::_objList.push_back(new Disco(0.70, 1.5, 0.5, 0.5, 0.5, 0, 0, 0));
	
	Sombrero::_tAf.rotar(-90, 1, 0, 0);
	Sombrero::_tAf.trasladar(PV3D(0, x, y, z));

}

Sombrero::~Sombrero(void){}
