
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include "Obstaculo.h"
#include "Circulo.h"



using namespace std;



class Triangulo : public Obstaculo
{

public:

	list<PV2D> _v;

	list<PV2D> _pointMid;

	GLdouble _ballRadius;

	PV2D _midSide[3];

	PV2D _normSide[3];

	list<Obstaculo*> _corteza;

	void draw();

	bool colision(const PV2D &p, const PV2D &v, GLdouble& tIn, PV2D& normalIn, const bool & hardMode);

	Triangulo(const list<PV2D> &pts, const GLdouble &ballRadius);

	Triangulo(void);

	~Triangulo(void);

};

