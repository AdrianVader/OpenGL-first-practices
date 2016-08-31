
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "Malla.h"

//Dada una cara devuelve la normal a esa cara
PV3D Malla::newellNormal(list<PV3D> &side){

	PV3D vect = PV3D(0,0,0,0);

	list<PV3D>::iterator it = side.begin();
	PV3D frst = side.front();
	for(int i = 0; i < side.size();i++){
		PV3D act = *it;
		it++;
		PV3D next;
		if(it == side.end())
			next = frst;
		else
			next = *it;
		
		vect._x += (act._y-next._y)*(act._z+next._z);
		vect._y += (act._z-next._z)*(act._x+next._x);
		vect._z += (act._x-next._x)*(act._y+next._y);
	}

	return vect.normalize();
}

Malla::Malla(void){}

Malla::~Malla(void){}