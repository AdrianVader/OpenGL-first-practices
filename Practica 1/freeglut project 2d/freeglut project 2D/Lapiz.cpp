
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include "Lapiz.h"



const Punto Lapiz::draw(const double &longitud){
	
	double RADIANS = 3.14159265/180;

	Punto destino = Punto(Lapiz::_origen._x + (cos(Lapiz::_orientacion * RADIANS)*longitud), Lapiz::_origen._y + (sin(Lapiz::_orientacion * RADIANS)*longitud));
	Lapiz::_origen = destino;
	return destino;

}

void Lapiz::turn(const double &grades){

	double suma = Lapiz::_orientacion + grades;
	int vueltas = suma / 360;

	if(suma >= 0){
		Lapiz::_orientacion = suma - vueltas*360;	
	}else{	
		Lapiz::_orientacion = 360 + (suma + vueltas*360);
	}

}

Lapiz::Lapiz(const Punto &punto, const double &orientacion){

	Lapiz::_origen = punto;
	int vueltas = orientacion/360;
	
	if(orientacion >= 0){
		Lapiz::_orientacion = orientacion - vueltas*360;
	}else{
		Lapiz::_orientacion = 360 + (orientacion + vueltas*360);
	}

}

Lapiz::Lapiz(void)
{
}

Lapiz::~Lapiz(void)
{
}
