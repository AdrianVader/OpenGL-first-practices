
/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
*/


#pragma once



#include <list>



#include "PV2D.h"



class Obstaculo
{

public:

	list<PV2D> _pointList;


	virtual void draw() = 0;

	virtual bool colision(const PV2D &p, const PV2D &v, GLdouble& tIn, PV2D& normalIn) = 0;

	void nada();

};

