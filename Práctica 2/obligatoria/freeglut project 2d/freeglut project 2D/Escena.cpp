
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include "escena.h"



void Escena::init(const int &WIDTH, const int &HEIGHT){

	// Scene visible area size
	Escena::_xLeft= 0.0;
	Escena::_xRight= WIDTH;
	Escena::_yBot= 0.0;
	Escena::_yTop= HEIGHT;

	Escena::_tHit = 0;

}

void Escena::createAll(const PV2D &pMid, const PV2D &move, const GLdouble &radius){

	Escena::_ball.createBall(pMid, move, radius);

	Escena::createScenery();

}

void Escena::createScenery(){

	list<PV2D> pointList;
	Obstaculo *triangle;
	
	// Up border triangle.
	pointList.push_back(PV2D(Escena::_xLeft - 200, Escena::_yTop));
	pointList.push_back(PV2D(Escena::_xRight + 200, Escena::_yTop));
	pointList.push_back(PV2D((Escena::_xRight - Escena::_xLeft)/2, Escena::_yTop + 100));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();
	
	// Down border triangle.
	pointList.push_back(PV2D(Escena::_xRight + 200, Escena::_yBot));
	pointList.push_back(PV2D(Escena::_xLeft - 200, Escena::_yBot));
	pointList.push_back(PV2D((Escena::_xRight - Escena::_xLeft)/2, Escena::_yBot - 100));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();
	
	// Left border triangle.
	pointList.push_back(PV2D(Escena::_xLeft, Escena::_yBot - 200));
	pointList.push_back(PV2D(Escena::_xLeft, Escena::_yTop + 200));
	pointList.push_back(PV2D(Escena::_xLeft - 100, (Escena::_yTop - Escena::_yBot)/2));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();

	// Right border triangle.
	pointList.push_back(PV2D(Escena::_xRight, Escena::_yTop + 200));
	pointList.push_back(PV2D(Escena::_xRight, Escena::_yBot - 200));
	pointList.push_back(PV2D(Escena::_xRight + 100, (Escena::_yTop - Escena::_yBot)/2));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();
	
	
	// Triangles in the scene.
	pointList.push_back(PV2D(400, 430));
	pointList.push_back(PV2D(330, 400));
	pointList.push_back(PV2D(420, 300));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();

	pointList.push_back(PV2D(550, 440));
	pointList.push_back(PV2D(480, 400));
	pointList.push_back(PV2D(590, 380));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();

	pointList.push_back(PV2D(500, 100));
	pointList.push_back(PV2D(580, 200));
	pointList.push_back(PV2D(520, 190));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();

	pointList.push_back(PV2D(100, 40));
	pointList.push_back(PV2D(250, 60));
	pointList.push_back(PV2D(130, 130));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();
	
	pointList.push_back(PV2D(400, 175));
	pointList.push_back(PV2D(450, 175));
	pointList.push_back(PV2D(455, 250));
	triangle = new Triangulo(pointList);
	Escena::_listaObstaculos.push_back(triangle);
	pointList.pop_front();
	pointList.pop_front();
	pointList.pop_front();

	// Circles in the scene.
	Circulo *circle1 = new Circulo(PV2D(315, 125), 50);
	Escena::_listaObstaculos.push_back(circle1);

	Circulo *circle2 = new Circulo(PV2D(30, 90), 40);
	Escena::_listaObstaculos.push_back(circle2);

	Circulo *circle3 = new Circulo(PV2D(375, 40), 10);
	Escena::_listaObstaculos.push_back(circle3);

	Circulo *circle4 = new Circulo(PV2D(550, 300), 30);
	Escena::_listaObstaculos.push_back(circle4);

	Circulo *circle5 = new Circulo(PV2D(90, 350), 80);
	Escena::_listaObstaculos.push_back(circle5);
	
	
}

void Escena::draw(){
	
	Escena::_ball.draw(Escena::_tHit);

	list<Obstaculo*>::iterator it = Escena::_listaObstaculos.begin();
	while(it != Escena::_listaObstaculos.end()){

		it._Ptr->_Myval->draw();

		it++;
	}

}

void Escena::step(){
	
	GLdouble tHit = DBL_MAX;
	GLdouble tMin = DBL_MAX;
	PV2D nHit;
	PV2D nMin;

	list<Obstaculo*>::iterator it = Escena::_listaObstaculos.begin();
	while(it != Escena::_listaObstaculos.end()){
		it._Ptr->_Myval->colision(Escena::_ball._mid, Escena::_ball._move, tHit, nHit);
		if(tHit >= 0 && tMin > tHit){
			tMin = tHit;
			nMin = nHit;
		}
		it++;
	}

	if(tMin <= sqrt(pow(Escena::_ball._speed._x, 2) + pow(Escena::_ball._speed._y, 2)))
		Escena::_ball._move = nMin;

	Escena::_tHit = tMin;

}

Escena::Escena(void)
{
}

Escena::~Escena(void)
{
}
