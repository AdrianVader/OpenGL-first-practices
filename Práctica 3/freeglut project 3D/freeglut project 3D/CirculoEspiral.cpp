
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "CirculoEspiral.h"



void CirculoEspiral::draw(){

	list<Cara>::iterator it = CirculoEspiral::_arrSid.begin();
	while(it != CirculoEspiral::_arrSid.end()){

		glColor3f(1.0, 1.0, 0.0);

		it->draw();
		it++;
	}

}


CirculoEspiral::CirculoEspiral(void){

	GLdouble radius = 3; // Radius of the spiral's inner circle
	const GLdouble PI = 3.14159;
	const GLdouble RAD = 0.0174532925;
	GLdouble side = 1.0; // Length of the side to aproximate the circle.
	GLint numPtsCircle = (2*radius*PI)/side; // Number of points to aproximate the circle.
	GLint slices = 270;

	CirculoEspiral::_numVert = numPtsCircle * slices;

	CirculoEspiral::_numNorm = CirculoEspiral::_numVert;

	CirculoEspiral::_numSid = numPtsCircle*(slices-1);

	CirculoEspiral::_arrVert = list<PV3D>();
	CirculoEspiral::_arrNorm = list<PV3D>();
	CirculoEspiral::_arrSid = list<Cara>();
	
	


	// Crear el círculo.
	//La espiral se crea usando el marco de frenet siguiendo c(x) = 0.1*cos(4*x*RAD) + 0.1*x*sin(4*x*RAD), 0, 0.1*sin(4*x*RAD) - 0.1*x*cos(4*x*RAD), 1
	int dist = 0;
	GLdouble alpha = 0;
	GLdouble inc = 360.0/numPtsCircle;
	for(int i = 0; i < numPtsCircle; i++){
		CirculoEspiral::_arrVert.push_back(PV3D(radius*cos(alpha*RAD), radius*sin(alpha*RAD), dist, 1));
		alpha += inc;
	}
	int contSides = CirculoEspiral::_arrVert.size();



	// Create the rest of the spiral.
	list<PV3D>::iterator it;
	for(int i = 1; i < slices; i+=3){
		it = CirculoEspiral::_arrVert.begin();
		for(int j = 0; j < contSides; j++){

			PV3D n, b ,t, c, cp, cpp, point;

			c = PV3D(0.1*cos(4*i*RAD) + 0.1*i*sin(4*i*RAD), 0, 0.1*sin(4*i*RAD) - 0.1*i*cos(4*i*RAD), 1);
			cp = PV3D(-0.4*sin(4*i*RAD) +(0.1*sin(4*i*RAD) + 0.4*i*cos(4*i*RAD)), 0, 0.4*cos(4*i*RAD) -(0.1*cos(4*i*RAD) - 0.4*i*sin(4*i*RAD)), 0);
			cpp = PV3D(-1.6*cos(4*i*RAD) +(0.8*cos(4*i*RAD) - 1.6*i*sin(4*i*RAD)), 0, -1.6*sin(4*i*RAD) -(-0.8*sin(4*i*RAD) - 1.6*i*cos(4*i*RAD)), 0);
			t = cp.normalize();
			b = PV3D(cp._y*cpp._z - cp._z*cpp._y,
				cp._z*cpp._x - cp._x*cpp._z,
				cp._x*cpp._y - cp._y*cpp._x,
				0).normalize();
			n = PV3D(b._y*t._z - b._z*t._y,
				b._z*t._x - b._x*t._z,
				b._x*t._y - b._y*t._x,
				0);

			point = PV3D(n._x*it->_x + b._x*it->_y + t._x*it->_z + c._x*it->_point,
						n._y*it->_x + b._y*it->_y + t._y*it->_z + c._y*it->_point,
						n._z*it->_x + b._z*it->_y + t._z*it->_z + c._z*it->_point,
						1);

			CirculoEspiral::_arrVert.push_back(PV3D(point._x, point._y, point._z, 1));
			
			it++;
		}
	}

	// Quitamos estos vértices de la lista simplemente para que se dibuje mejor la espiral y se vea más clara
	for(int i = 0; i < contSides; i++){
		CirculoEspiral::_arrVert.pop_front();
	}

	// Store the faces.
	list<PV3D>::iterator itV1 = CirculoEspiral::_arrVert.begin();
	list<PV3D>::iterator itV2 = CirculoEspiral::_arrVert.begin();
	for(int i = 0; i < numPtsCircle;i++)
		itV2++;
	list<PV3D> l = list<PV3D>();
	PV3D fstVertAct = *itV1;
	PV3D fstVertNext = *itV2;
	PV3D vertAct1;
	PV3D vertAct2 = *itV1;
	PV3D vertNext1;
	PV3D vertNext2 = *itV2;
	int cont = 0;
	do{

		vertAct1 = *itV1;
		vertNext1 = *itV2;
		
		itV1++;
		itV2++;

		if(cont < contSides-1){
			vertAct2 = *itV1;
			vertNext2 = *itV2;
			cont++;
		}else{
			vertAct2 = fstVertAct;
			vertNext2 = fstVertNext;
			cont = 0;
			if(itV2 !=  CirculoEspiral::_arrVert.end()){
				fstVertAct = *itV1;
				fstVertNext = *itV2;
			}
		}

		l.push_back(vertAct1);
		l.push_back(vertAct2);
		l.push_back(vertNext2);
		l.push_back(vertNext1);

		// calcula la normal de la cara, con l(vértices de la cara) y lo mete donde está listNorm.
		// Generate normals.
		PV3D norm = CirculoEspiral::newellNormal(l);
		
		list<VerticeNormal> listVertNorm = list<VerticeNormal>();
		
		list<PV3D>::iterator itL = l.begin();
		for(int i = 0; i < l.size();i++){
			listVertNorm.push_back(VerticeNormal(*itL, norm));
			itL++;
			CirculoEspiral::_arrNorm.push_back(norm);
		}

		CirculoEspiral::_arrSid.push_back(Cara(listVertNorm.size(), listVertNorm));
		l.clear();
		
	}while(itV2 != CirculoEspiral::_arrVert.end());

}

CirculoEspiral::~CirculoEspiral(void){}