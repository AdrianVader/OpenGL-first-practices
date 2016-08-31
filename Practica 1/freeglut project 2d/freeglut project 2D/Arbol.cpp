
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/

#include <iostream>
#include "Arbol.h"



void Arbol::initTree(const Punto &pMid, const GLdouble &side){

	//El tronco empieza siendo marrón y se va transformando en verde hacia las hojas
	float color [3] = {0.70,0.30,0.00};

	Cuadrado cuadrado = Cuadrado();
	Punto *pIni = new Punto(pMid._x-side/2, pMid._y-side/2);
	cuadrado.createSquare(*pIni, side, 0, color);

	list<Cuadrado> primerNivel = list<Cuadrado>();
	primerNivel.push_back(cuadrado);
	Arbol::_arbol.push_back(primerNivel);

}

void Arbol::nextLevel(const Cuadrado &cuadrado){
	
	double RADIANS = 3.14159265/180;
	//Ángulo que define la simetría/asimetría del árbol
	//Representa el ángulo izquierdo del triángulo, entre el cuadrado padre y el cuadrado hijo izquierdo
	double angulo = 40;

	//EL color hace un degradado de marrón a verde
	float c0 = cuadrado._color[0], c1 = cuadrado._color[1];
	if(cuadrado._color[0] > 0)
		c0 = cuadrado._color[0]-0.02;
	if(cuadrado._color[1] < 0.80)
		c1 = cuadrado._color[1]+0.05;

	float color[3] = {c0,c1,0.00};

	Cuadrado *izq = new Cuadrado();
	double sideLeft;
	//Vértice inicial del cuadrado hijo izquierdo
	double x = cuadrado._pointList.front()._x + cos((cuadrado._orientacion + 90)*RADIANS)*cuadrado._side;
	double y = cuadrado._pointList.front()._y + sin((cuadrado._orientacion + 90)*RADIANS)*cuadrado._side;
	Punto aux = Punto(x, y);
	sideLeft = cuadrado._side * cos(angulo*RADIANS);
	double orientacion = cuadrado._orientacion + angulo;
	izq->createSquare(aux, sideLeft, orientacion, color);
	
	Cuadrado *dcha = new Cuadrado();
	double sideRight;
	sideRight = cuadrado._side * sin(angulo*RADIANS);
	//Vértice inicial del cuadrado hijo derecho
	x += cos(orientacion*RADIANS)*sideLeft;
	y += sin(orientacion*RADIANS)*sideLeft;
	aux = Punto(x, y);
	orientacion  -= 90;
	dcha->createSquare(aux, sideRight, orientacion, color);
	
	Arbol::_arbol.back().push_back(*izq);
	Arbol::_arbol.back().push_back(*dcha);
	
}

void Arbol::createNextLevel(){
	
	list<Cuadrado>::iterator it = Arbol::_arbol.back().begin();
	list<Cuadrado>::iterator end = Arbol::_arbol.back().end();
	Arbol::_arbol.push_back(list<Cuadrado>());
	while(it != end){
	
		Arbol::nextLevel(*it);
		it++;
	
	}
	
}

void Arbol::deleteLastLevel(){

	Arbol::_arbol.pop_back();

}

void Arbol::draw(){

	list<list<Cuadrado>>::iterator level = Arbol::_arbol.begin();

	while(level != Arbol::_arbol.end()){
	
		list<Cuadrado>::iterator square = level->begin();
		while(square != level->end()){
		
			square->draw();

			square++;
		
		}

		level++;
	
	}

}

const int &Arbol::size(){

	return Arbol::_arbol.size();

}

void Arbol::colision(const Punto &p){
	
	bool found = false;

	list<list<Cuadrado>>::iterator level = Arbol::_arbol.begin();

	while(level != Arbol::_arbol.end()){

		list<Cuadrado>::iterator square = level->begin();
		while(square != level->end()){
		
			if(square->colision(p, found))
				found = true;

			square++;
		
		}

		level++;
	
	}
	
}



Arbol::Arbol(void)
{
}

Arbol::~Arbol(void)
{
}
