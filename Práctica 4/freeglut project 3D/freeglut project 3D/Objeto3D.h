
/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
*/


#pragma once



#include "TAfin.h"



using namespace std;



class Objeto3D
{

public:

	TAfin _tAf;

	GLdouble _r, _g, _b;


	virtual void draw() = 0;

	Objeto3D(void);

	~Objeto3D(void);

};