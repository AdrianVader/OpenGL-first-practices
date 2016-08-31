
/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
*/


#pragma once



#include <math.h>

#include "Punto.h"



using namespace std;



class Lapiz
{

public:

	Punto _origen;

	double _orientacion;


	const Punto draw(const double &longitud);

	void turn(const double &grades);

	Lapiz(const Punto &punto, const double &orientacion);

	Lapiz(void);

	~Lapiz(void);

};

