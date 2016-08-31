
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "Cara.h"
#include "VerticeNormal.h"
	


void Cara::draw(){

	list<VerticeNormal>::iterator it = Cara::_norm.begin();
	VerticeNormal frst = *it, scnd, thrd;
	it++;
	thrd = *it;
	it++;
	while(it != Cara::_norm.end()){
		
		scnd = thrd;
		thrd = *it;

		if(it != Cara::_norm.end()){
			glBegin(GL_POLYGON);/*GL_POLYGON GL_LINE_LOOP GL_POINTS*/

			glNormal3f(frst._norm._x, frst._norm._y, frst._norm._z);
			glVertex3f(frst._vert._x, frst._vert._y, frst._vert._z);
		
			glNormal3f(scnd._norm._x, scnd._norm._y, scnd._norm._z);
			glVertex3f(scnd._vert._x, scnd._vert._y, scnd._vert._z);
			
			glNormal3f(thrd._norm._x, thrd._norm._y, thrd._norm._z);
			glVertex3f(thrd._vert._x, thrd._vert._y, thrd._vert._z);
		
			glEnd();
		}
		it++;
	}

}

Cara::Cara(GLint numVert, list<VerticeNormal> norm){
	
	Cara::_numVert = numVert;
	Cara::_norm = norm;

}

Cara::Cara(void){}

Cara::~Cara(void){}