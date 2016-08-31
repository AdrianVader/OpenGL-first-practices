
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include "Pelota.h"



void Pelota::createBall(const PV2D &mid,const PV2D &movement, const GLdouble &radius){

	const GLdouble PI = 3.14159265359;

	Pelota::_mid = mid;
	Pelota::_radius = radius;
	Pelota::_move = movement;
	Pelota::_vel = 2;
	Pelota::_speed = PV2D(movement._x*Pelota::_vel, movement._y*Pelota::_vel);
	
	GLdouble side = 5;
	GLdouble perimetro = 2*radius*PI;
	GLdouble alpha = 360/(perimetro/side);

	Lapiz l = Lapiz(PV2D(Pelota::_mid._x , Pelota::_mid._y), 0);
	PV2D punto;
	for(int i = 0; i < 360/alpha; i++){
		Pelota::_circle.push_back(PV2D(l.draw(Pelota::_radius)._x-Pelota::_mid._x, l.draw(Pelota::_radius)._y-Pelota::_mid._y));
		l.turn(alpha);
	}

}

void Pelota::draw(GLdouble &tHit){

	GLdouble mod = sqrt(pow(Pelota::_speed._x, 2) + pow(Pelota::_speed._y, 2));
	if(abs(tHit) <= mod){
		Pelota::_mid._x += (tHit/mod)*Pelota::_speed._x;
		Pelota::_mid._y += (tHit/mod)*Pelota::_speed._y;
	}else{
		Pelota::_mid._x += Pelota::_speed._x;
		Pelota::_mid._y += Pelota::_speed._y;
	}
	
	Pelota::_speed = PV2D(Pelota::_move._x*Pelota::_vel, Pelota::_move._y*Pelota::_vel);

	tHit = 0;



	glColor3f(1.0,0.0,0.0);

	glBegin ( GL_POLYGON );

	list<PV2D>::iterator it = Pelota::_circle.begin();
	while(it != Pelota::_circle.end()){
		glVertex2d(Pelota::_mid._x + it->_x, Pelota::_mid._y + it->_y);
		it++;
	}

    glEnd () ;
	
	//Descomentar esta sección si se quiere pintar el centro de la pelota:
	//***********************************************************************************************
	/*
	glColor3f(0.0,0.0,0.0);
	glBegin ( GL_LINES );
	glVertex2d(Pelota::_mid._x - 10, Pelota::_mid._y);
	glVertex2d(Pelota::_mid._x + 10, Pelota::_mid._y);
	glVertex2d(Pelota::_mid._x, Pelota::_mid._y - 10);
	glVertex2d(Pelota::_mid._x, Pelota::_mid._y + 10);
    glEnd () ;
	*/
	//***********************************************************************************************
}

Pelota::Pelota(void)
{
}

Pelota::~Pelota(void)
{
}
