
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "MunecoDeNieve.h"
#include "Esfera.h"
#include "Sombrero.h"
#include "Malla.h"
	


void MunecoDeNieve::draw(){

	list<Objeto3D*>::iterator it = MunecoDeNieve::_objList.begin();
	while(it != MunecoDeNieve::_objList.end()){

		it._Ptr->_Myval->draw();

		it++;
	}

}

MunecoDeNieve::MunecoDeNieve(void){

	GLdouble altura = 1.5;
	GLdouble grosor = 0;
	GLdouble prof = 0;

	// Cuerpo.
	MunecoDeNieve::_objList.push_back(new Esfera(1.5, 1.0, 1.0, 1.0, prof, altura, grosor));

	altura += 1.5;
	altura += 0.8;
	// Cabeza.
	MunecoDeNieve::_objList.push_back(new Esfera(1, 1.0, 1.0, 1.0, prof, altura, grosor));

	altura += 0.8;
	// Sombrero.
	MunecoDeNieve::_objList.push_back(new Sombrero(prof, altura, grosor));

	altura -= 0.8;
	grosor += 1;
	// Nariz.
	MunecoDeNieve::_objList.push_back(new Cilindro(0.15, 0.0, 1, 0.7, 0.4, 0.0, prof, altura, grosor));

	altura += 0.3;
	prof += 0.25;
	// Ojos.
	MunecoDeNieve::_objList.push_back(new Cilindro(0.15, 0.15, 0.05, 0, 0, 0, prof, altura, grosor));
	prof = -prof;
	MunecoDeNieve::_objList.push_back(new Cilindro(0.15, 0.15, 0.05, 0, 0, 0, prof, altura, grosor));

	altura = 1.5;
	grosor = 1.5;
	prof = 0;
	// Botones.
	MunecoDeNieve::_objList.push_back(new Cilindro(0.25, 0.25, 0.15, 0.0, 0.0, 0.0, prof, altura, grosor));
	altura += 0.75;
	grosor -= 0.2;
	MunecoDeNieve::_objList.push_back(new Cilindro(0.25, 0.25, 0.15, 0.0, 0.0, 0.0, prof, altura, grosor, -25, 1, 0, 0));
	altura -= 0.75*2;
	MunecoDeNieve::_objList.push_back(new Cilindro(0.25, 0.25, 0.15, 0.0, 0.0, 0.0, prof, altura, grosor, 25, 1, 0, 0));

	altura = 0;
	grosor = 0;
	prof = 0;
	// Suelo.
	MunecoDeNieve::_objList.push_back(new Malla(5, 0.5, prof, altura, grosor, 90, 1, 0, 0));


	MunecoDeNieve::_objList.push_back(new Disco(0, 1, 0, 1, 0, 0, 4, 4)); // Disco para que se vean las luces de los ojos

}

MunecoDeNieve::~MunecoDeNieve(void){}