
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



#include "Obstaculo.h"
#include "Lapiz.h"



using namespace std;



class Circulo : public Obstaculo
{

public:

	PV2D _mid;

	GLdouble _radius;

	int _nSides;

	list<PV2D> _normSide;


	void draw();

	bool colision(const PV2D &p, const PV2D &v, GLdouble& tIn, PV2D& normalIn);

	PV2D reflexiona(const PV2D &v, const PV2D &n);

	PV2D pincha(const PV2D &v, const int &vertice);

	Circulo(const PV2D &mid, const GLdouble &radius);

	Circulo(void);

	~Circulo(void);

};
