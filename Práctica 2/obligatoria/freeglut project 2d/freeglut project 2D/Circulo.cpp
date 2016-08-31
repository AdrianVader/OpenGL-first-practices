
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include "Circulo.h"


Circulo::Circulo(const PV2D &mid, const GLdouble &radius){
	
	const GLdouble PI = 3.14159265359;

	Circulo::_mid = mid;
	Circulo::_radius = radius;
	
	GLdouble side = 5;
	GLdouble perimetro = 2*radius*PI;
	GLdouble alpha = 360/(perimetro/side);

	Lapiz l = Lapiz(PV2D(Circulo::_mid._x , Circulo::_mid._y), 0);

	PV2D first = PV2D(l.draw(radius)._x-Circulo::_mid._x, l.draw(radius)._y-Circulo::_mid._y), actual, next = PV2D(l.draw(radius)._x-Circulo::_mid._x, l.draw(radius)._y-Circulo::_mid._y);

	for(int i = 0; i < 360/alpha;i++){
		actual = next;
		Circulo::_pointList.push_back(PV2D(l.draw(radius)._x-Circulo::_mid._x, l.draw(radius)._y-Circulo::_mid._y));
		next = Circulo::_pointList.back();
		l.turn(alpha);

		if(actual._x != next._x && actual._y != next._y){
			GLdouble x = (next._x+actual._x)/2, y = (next._y+actual._y)/2, mod = sqrt(pow(x, 2) + pow(y,2));
			PV2D norm = PV2D(x/mod, y/mod);
			Circulo::_normSide.push_back(norm);
		}
	}
	actual = next;
	next = first;
	GLdouble x = (next._x+actual._x)/2, y = (next._y+actual._y)/2, mod = sqrt(pow(x, 2) + pow(y,2));
	PV2D norm = PV2D(x/mod, y/mod);
	Circulo::_normSide.push_back(norm);

	Circulo::_nSides = 360/alpha;

}



void Circulo::draw(){

	glColor3f(0.0,1.0,0.0);

	glBegin ( GL_POLYGON );

	list<PV2D>::iterator it = Circulo::_pointList.begin();
	while(it != Circulo::_pointList.end()){
		glVertex2d(Circulo::_mid._x + it->_x, Circulo::_mid._y + it->_y);
		it++;
	}

    glEnd () ;
}

bool Circulo::colision(const PV2D &p, const PV2D &v, GLdouble& tIn, PV2D& normalIn){

	GLdouble a = v._x*v._x + v._y*v._y;
	GLdouble cpX = p._x- Circulo::_mid._x;
	GLdouble cpY = p._y- Circulo::_mid._y;
	GLdouble b = 2 * (cpX * v._x + cpY * v._y);
	GLdouble c = cpX*cpX + cpY*cpY - pow(Circulo::_radius, 2);
	GLdouble disc = pow(b, 2) - 4*a*c;

	if(disc <= 0){
		return false;	//vamos a considerar que rozar no cuenta como intersección
	}else{
		GLdouble t1 = (-b - sqrt(disc))/(2*a);
		GLdouble t2 = (-b + sqrt(disc))/(2*a);
		if(t1 <= t2)
			tIn = t1;
		else
			tIn = t2;
	}

	PV2D n = PV2D((p._x + tIn*v._x)-Circulo::_mid._x, (p._y + tIn*v._y)-Circulo::_mid._y);
	normalIn = reflexiona(v, n);

	return true;
}

PV2D Circulo::reflexiona(const PV2D &v, const PV2D &n){

	GLdouble a = (v._x*n._x + v._y*n._y) / (n._x*n._x + n._y*n._y);
	PV2D an2 = PV2D(2*a*n._x, 2*a*n._y);
	return PV2D(v._x-an2._x, v._y-an2._y);

}

PV2D Circulo::pincha(const PV2D &v, const int &vertice){
	
	
	list<PV2D>::iterator it = Circulo::_pointList.begin();
	for(int i = 0; i < vertice;i++)
		it++;

	
	GLdouble a = (v._x*it->_x + v._y*it->_y) / (it->_x*it->_x + it->_y*it->_y);
	PV2D an2 = PV2D(2*a*it->_x, 2*a*it->_y);
	return PV2D(v._x-an2._x, v._y-an2._y);

}



Circulo::Circulo(void)
{
}

Circulo::~Circulo(void)
{
}
