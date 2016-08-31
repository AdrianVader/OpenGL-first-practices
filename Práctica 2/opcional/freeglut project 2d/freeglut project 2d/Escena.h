
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

#include <list>


#include "Pelota.h"
#include "Obstaculo.h"
#include "Triangulo.h"
#include "Circulo.h"

#include "PV2D.h"



using namespace std;



class Escena
{

public:

	Pelota _ball;
	list<Obstaculo*> _listaObstaculos;

	// Scene visible area size
	GLdouble _xLeft, _xRight, _yBot, _yTop;

	GLdouble _tHit;
	bool _hardMode;


	void init(const int &WIDTH, const int &HEIGHT, bool hard);

	void draw();

	void step();
	
	void createAll(const PV2D &pMid, const PV2D &move, const GLdouble &radius);

	void createScenery(const GLdouble &radius);

	Escena(void);

	~Escena(void);

};

