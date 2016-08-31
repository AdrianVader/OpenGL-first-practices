
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

#include "Lapiz.h"
#include "Punto.h"



using namespace std;



class Cuadrado
{

public:

	double _side;

	double _orientacion;
	list <Punto> _pointList;

	bool _initialColor;

	float _color[3];


	void createSquare(const Punto &p, const double &side, const double &orientacion, float color[3]);

	void draw();

	const bool &colision(const Punto &p, const bool &found);

	void changeColor();

	const bool &between(const double &mid, const double &ini, const double &end);
	
	Cuadrado(void);

	~Cuadrado(void);

};

