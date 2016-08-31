
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "VerticeNormal.h"


VerticeNormal::VerticeNormal(const PV3D &vert, const PV3D &norm){
	VerticeNormal::_vert = PV3D(vert._x, vert._y, vert._z, 1);
	VerticeNormal::_norm = PV3D(norm._x, norm._y, norm._z, 0);
}

VerticeNormal::VerticeNormal(void){}

VerticeNormal::~VerticeNormal(void){}