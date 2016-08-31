
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include <math.h>

#include "PV2D.h"



using namespace std;



class Lapiz
{

public:

	PV2D _origen;

	double _orientacion;


	const PV2D draw(const double &longitud);

	void turn(const double &grades);

	Lapiz(const PV2D &punto, const double &orientacion);

	Lapiz(void);

	~Lapiz(void);

};

