
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#include "Triangulo.h"



PV2D reflexiona(const PV2D &v, const PV2D &n);
PV2D pincha(const int &vertice, list<PV2D> &pointList);



Triangulo::Triangulo(const list<PV2D> &pts, const GLdouble &ballRadius){

	Triangulo::_pointList = pts;
	Triangulo::_ballRadius = ballRadius;

	list<PV2D>::iterator it = Triangulo::_pointList.begin();
	PV2D first = *it;
	PV2D actual;
	PV2D next;
	
	PV2D mid = PV2D(0, 0);
	while(it != Triangulo::_pointList.end()){
		mid._x += it->_x;
		mid._y += it->_y;
		it++;
	}
	mid._x /= 3;
	mid._y /= 3;

	it = Triangulo::_pointList.begin();
	int i = 0;
	while(it != Triangulo::_pointList.end()){

		actual = *it;
		it++;
		if(it != Triangulo::_pointList.end())
			next = *it;
		else
			next = first;

		Triangulo::_pointMid.push_back(PV2D((next._x + actual._x)/2, (next._y + actual._y)/2));
		Triangulo::_v.push_back(PV2D((next._y - actual._y), -(next._x - actual._x))); // Normalized vector.
		
		Triangulo::_midSide[i] = PV2D((actual._x+next._x)/2, (actual._y+next._y)/2);
		GLdouble modV = sqrt(pow((next._y-actual._y), 2) + pow((next._x-actual._x), 2));
		Triangulo::_normSide[i] = PV2D((next._y-actual._y)/modV, (-(next._x-actual._x))/modV);

		if(ballRadius > 0){
			list<PV2D> auxCorteza;
			auxCorteza.push_back(PV2D(mid._x, mid._y));
			auxCorteza.push_back(PV2D(actual._x+(Triangulo::_normSide[i]._x)*ballRadius, actual._y+(Triangulo::_normSide[i]._y)*ballRadius));
			auxCorteza.push_back(PV2D(next._x+(Triangulo::_normSide[i]._x)*ballRadius, next._y+(Triangulo::_normSide[i]._y)*ballRadius));
			Triangulo::_corteza.push_back(new Triangulo(auxCorteza, 0));
		}

		i++;

	}

	it = Triangulo::_pointList.begin();
	while(it != Triangulo::_pointList.end()){
		Triangulo::_corteza.push_back(new Circulo(*it, Triangulo::_ballRadius, 0));
		it++;
	}

}



void Triangulo::draw(){
	
	glColor3f(0.0,0.0,1.0);

	glBegin ( GL_POLYGON );

	list<PV2D>::iterator it = Triangulo::_pointList.begin();
	while(it != Triangulo::_pointList.end()){
		glVertex2d(it->_x, it->_y);
		it++;
	}

	glEnd();

}

bool Triangulo::colision(const PV2D &p, const PV2D &v, GLdouble& tIn, PV2D& normalIn, const bool & hardMode){

	if(hardMode){

		GLdouble tHit = DBL_MAX;
		GLdouble tMin = DBL_MAX;
		PV2D nHit;
		PV2D nMin;
		bool found = false;

		list<Obstaculo*>::iterator it = Triangulo::_corteza.begin();
		while(it != Triangulo::_corteza.end()){
			if(it._Ptr->_Myval->colision(p, v, tHit, nHit, false))
				found = true;
			if(tHit >= 0 && tMin > tHit){
				tMin = tHit;
				nMin = nHit;
			}
			it++;
		}

		tIn = tMin;
		normalIn = nMin;

		return found;

	}else{

		PV2D vN = PV2D(v._y, -v._x);
		PV2D aux; // -> del punto a vértice i del triángulo.
		list<PV2D> vect;
		list<GLdouble> dist;
		list<GLdouble> proy;
		list<GLint> sign;

		list<PV2D>::iterator it = Triangulo::_pointList.begin();
		while(it != Triangulo::_pointList.end()){

			vect.push_back(PV2D(it->_x - p._x, it->_y - p._y)); // Vector from the point(ball mid) to triangle's points.

			aux = PV2D(it->_x - p._x, it->_y - p._y);
			dist.push_back(aux._x*vN._x + aux._y*vN._y);
			proy.push_back(aux._x*v._x + aux._y*v._y);
		
			if(dist.back() <= 0.0001 && dist.back() >= -0.0001)
				sign.push_back(0);
			else if(dist.back() > 0.0001)
				sign.push_back(1);
			else
				sign.push_back(-1);

			it++;
		}

		GLint sum = 0;
		list<GLint>::iterator itS = sign.begin();
		while(itS != sign.end()){
			sum += *itS;
			itS++;
		}
		if(abs(sum) == 3) return false;

		GLint nHits= 0; GLdouble hit[3]; PV2D n[3];
	
		itS = sign.begin();
		list<GLdouble>::iterator itP = proy.begin();
		list<GLdouble>::iterator itD = dist.begin();
		GLint firstS = *itS, actualS, nextS;
		GLdouble firstP = *itP, actualP, nextP;
		GLdouble firstD = *itD, actualD, nextD;
		int i = 0;
		while(itS != sign.end()){

			actualS = *itS;
			itS++;
			if(itS != sign.end())
				nextS = *itS;
			else
				nextS = firstS;

			actualP = *itP;
			itP++;
			if(itP != proy.end())
				nextP = *itP;
			else
				nextP = firstP;

			actualD = *itD;
			itD++;
			if(itD != dist.end())
				nextD = *itD;
			else
				nextD = firstD;

			if(actualS*nextS < 0){
				hit[nHits] = ((actualP*nextD) - (actualD*nextP)) / (nextD-actualD);
				n[nHits] = reflexiona(v, Triangulo::_normSide[i]); // vector from tringle’s center to Pi
				nHits++;
			}
			i++;
		}

		if(nHits < 2){
			itS = sign.begin();
			itP = proy.begin();
			int j = 0;
			while(itS != sign.end()){
				if(*itS == 0){
					hit[nHits] = *itP;
					n[nHits]= pincha(j, Triangulo::_pointList);
					nHits++;
				}

				itS++;
				itP++;
				j++;
			}
		}

		GLint m = 0;
		tIn = hit[0];
		for(int i = 1; i < nHits; i++){
			if(hit[i] < tIn){
				m = i;
				tIn = hit[i];
			}
		}
		normalIn= n[m];
		return true;

	}

}

PV2D reflexiona(const PV2D &v, const PV2D &n){

	GLdouble a = (v._x*n._x + v._y*n._y) / (n._x*n._x + n._y*n._y);
	PV2D an2 = PV2D(2*a*n._x, 2*a*n._y);
	return PV2D(v._x-an2._x, v._y-an2._y);

}

PV2D pincha(const int &vertice, list<PV2D> &pointList){

	GLdouble sumX = 0, sumY = 0;
	PV2D vert;
	list<PV2D>::iterator it = pointList.begin();
	int cont = 0;
	while(it != pointList.end()){
		sumX += it->_x;
		sumY += it->_y;
		if(vertice == cont)
			vert = *it;
		it++;
		cont++;
	}

	sumX /= 3;
	sumY /= 3;

	PV2D r = PV2D(vert._x-sumX, vert._y-sumY);
	GLdouble mod = sqrt(pow(r._x, 2) + pow(r._y, 2));
	PV2D rN = PV2D(r._x/mod, r._y/mod);

	return rN;

}



Triangulo::Triangulo(void)
{
}

Triangulo::~Triangulo(void)
{
}

