/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/

#include <iostream>
#include "Satelite.h"

GLdouble radius;

void Satelite::draw(){

	list<Cara>::iterator it = Satelite::_arrSid.begin();
	while(it != Satelite::_arrSid.end()){
		
		glColor3f(0.0, 0.0, 1.0);

		it->draw();
		it++;
	}

}


Satelite::Satelite(void)
{

	/*GLdouble */radius = 0.5; // Radius of the setelite's circle.
	const GLdouble PI = 3.14159;
	const GLdouble RAD = 0.0174532925;
	GLdouble side = 0.1; // Length of the side to aproximate the circle.
	GLint numPtsCircle = (2*radius*PI)/side; // Number of points to aproximate the circle.
	GLint slices = 10; //Capas que tiene el satélite

	Satelite::_numVert = numPtsCircle * slices;

	Satelite::_numNorm = Satelite::_numVert;

	Satelite::_numSid = numPtsCircle*(slices-1);

	Satelite::_arrVert = list<PV3D>();
	Satelite::_arrNorm = list<PV3D>();
	Satelite::_arrSid = list<Cara>();
	
	// Circle based on C(t) = (r*cos(t), r*sin(t), 0). Axis XY
	// Create the circle.
	GLdouble dist = 0;
	GLdouble alpha = 0;
	GLdouble inc = 360.0/numPtsCircle;
	for(int i = 0; i < numPtsCircle; i++){
		Satelite::_arrVert.push_back(PV3D(radius*cos(alpha*RAD), radius*sin(alpha*RAD), dist, 1));
		alpha += inc;
	}
	int contSides = Satelite::_arrVert.size();
	
	// Create the head by extrusion.
	int distOld = dist;
	dist += 1;
	list<PV3D>::iterator it = Satelite::_arrVert.begin();
	const int MAX = slices - 2; // Capas/rodajas que tiene la antena.
	for(int j = MAX-1; j >= 0;j--){
		alpha = 0;
		for(int i = 0; i < contSides;i++){
			Satelite::_arrVert.push_back(PV3D(it->_x -(cos(alpha*RAD))*((1.0f/MAX)*radius), it->_y -(sin(alpha*RAD))*((1.0f/MAX)*radius), it->_z +((1.0f/MAX)*(dist-distOld)), 1)); // CAMBIAR: ESTO 0 POR (1.0f/MAX)*radius ESTO.
			it++;
			alpha += inc;
		}
	}

	//Zona levemente levantada
	distOld = dist;
	dist += 0.3;
	alpha = 0;
	for(int i = 0; i < contSides;i++){
		Satelite::_arrVert.push_back(PV3D(it->_x +(cos(alpha*RAD))*radius, it->_y +(sin(alpha*RAD))*radius, it->_z +(dist-distOld), 1));
		it++;
		alpha += inc;
	}

	// Create the cylinder by extrusion.
	distOld = dist;
	dist += 0.8;
	for(int i = 0; i < contSides;i++){
		Satelite::_arrVert.push_back(PV3D(it->_x, it->_y, it->_z+ (dist-distOld), 1));
		it++;
	}



	// Store the faces.
	list<PV3D>::iterator itV1 = Satelite::_arrVert.begin();
	list<PV3D>::iterator itV2 = Satelite::_arrVert.begin();
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
			if(itV2 !=  Satelite::_arrVert.end()){
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
		PV3D norm = Satelite::newellNormal(l);
		
		list<VerticeNormal> listVertNorm = list<VerticeNormal>();
		
		list<PV3D>::iterator itL = l.begin();
		for(int i = 0; i < l.size();i++){
			listVertNorm.push_back(VerticeNormal(*itL, norm));
			itL++;
			Satelite::_arrNorm.push_back(norm);
		}

		Satelite::_arrSid.push_back(Cara(listVertNorm.size(), listVertNorm));
		l.clear();
		
	}while(itV2 != Satelite::_arrVert.end());


}

void creaPanel(){
	GLdouble length = 2;
	GLdouble width = 2*radius;

}

Satelite::~Satelite(void)
{
}
