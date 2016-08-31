
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include "Obstaculo.h"



using namespace std;



class Triangulo : public Obstaculo
{

public:

	list<PV2D> _v;

	list<PV2D> _pointMid;

	PV2D _midSide[3];

	PV2D _normSide[3];

	void draw();

	bool colision(const PV2D &p, const PV2D &v, GLdouble& tIn, PV2D& normalIn);

	Triangulo(const list<PV2D> &pts);

	Triangulo(void);

	~Triangulo(void);

};

