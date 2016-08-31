
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
#include <math.h>


#include "PV2D.h"
#include "Lapiz.h"



using namespace std;



class Pelota
{

public:

	GLdouble _radius;

	PV2D _mid;

	PV2D _move;

	list<PV2D> _circle;
	
	GLdouble _vel;

	PV2D _speed;


	void createBall(const PV2D &mid,const PV2D &movement, const GLdouble &radius);

	void draw(GLdouble &tHit);

	Pelota(void);

	~Pelota(void);

};

