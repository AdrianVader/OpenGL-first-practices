
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include "escena.h"
#include "Cuadrado.h"



void Escena::init(const int &WIDTH, const int &HEIGHT){

	// Scene visible area size
	Escena::_xLeft= 0.0;
	Escena::_xRight= WIDTH;
	Escena::_yBot= 0.0;
	Escena::_yTop= HEIGHT;

	Escena::_arbolPitagoras = Arbol();

}

void Escena::draw(){

	Escena::_arbolPitagoras.draw();

}

const int &Escena::sizeOfTree(){
	
	return Escena::_arbolPitagoras.size();

}

void Escena::initTree(const Punto &p, const GLdouble &side){

	Escena::_arbolPitagoras.initTree(p, side);

}

void Escena::colision(const Punto &p){
	
	Escena::_arbolPitagoras.colision(p);

}

void Escena::createNextLevel(){

	Escena::_arbolPitagoras.createNextLevel();

}

Escena::Escena(void)
{
}

Escena::~Escena(void)
{
}
