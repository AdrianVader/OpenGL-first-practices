
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include <math.h>
#include "PV3D.h"


//Normaliza un vector
PV3D PV3D::normalize(){

	GLdouble mod = sqrt( (pow(PV3D::_x, 2) + pow(PV3D::_y, 2) + pow(PV3D::_z, 2)) );

	return PV3D(PV3D::_x/mod, PV3D::_y/mod, PV3D::_z/mod, PV3D::_point);
}

PV3D PV3D::productoV(const PV3D &v){

	PV3D nuevo = PV3D(
		PV3D::_y*v._z - PV3D::_z*v._y,
		PV3D::_z*v._x - PV3D::_x*v._z,
		PV3D::_x*v._y - PV3D::_y*v._x,
		0);

	return nuevo;

}

GLfloat PV3D::productoE(const PV3D &v){

	return PV3D::_x*v._x + PV3D::_y*v._y + PV3D::_z*v._z;

}

PV3D::PV3D(const GLdouble &x, const GLdouble &y, const GLdouble &z, const GLint &point){

	PV3D::_x = x;
	PV3D::_y = y;
	PV3D::_z = z;
	PV3D::_point = point;

}

PV3D::PV3D(void){}

PV3D::~PV3D(void){}