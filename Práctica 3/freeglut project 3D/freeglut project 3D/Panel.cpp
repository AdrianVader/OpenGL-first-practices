/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/

#include <iostream>
#include "Panel.h"


Panel::Panel(GLdouble width){

	//Inicialización de variables
	Panel::_numVert = 32;
	Panel::_numNorm = Panel::_numVert;
	Panel::_numSid = 22;

	Panel::_arrVert = list<PV3D>();
	Panel::_arrNorm = list<PV3D>();
	Panel::_arrSid = list<Cara>();


	//Puntos iniciales donde se empezará a dibujar el panel
	GLdouble puntoAncho;		//x
	GLdouble puntoGrosor;		//y
	GLdouble puntoLongitud = 0;	//z

	GLdouble length = 3;	//Longitud del panel
	GLdouble grosor = 0.3;	//Grosor o alto del panel

	PV3D p1;
	PV3D p2;
	PV3D p3;
	PV3D p4;

	list<PV3D> arrAux = list<PV3D>();	//Lista auxiliar para guardar los 8 puntos relevantes a la hora de dibujar las caras a lo largo

	PV3D punto;

	//GENERACIÓN DE VÉRTICES
	//Guardamos los vértices que generan las rejillas de los extremos
	for(int z = 0; z < 2; z++){
		
		puntoGrosor = 0;

		for(int i = 0; i < 4; i++){

			puntoAncho = 0;

			for(int j = 0; j < 4; j++){

				punto = PV3D(puntoAncho, puntoGrosor, puntoLongitud, 1);
				Panel::_arrVert.push_back(punto);
				puntoAncho += width/3.0;

				//Si el punto es uno de los necesarios para dibujar el panel a lo largo, lo guardamos
				if(j==0 && i== 0)
					p1 = punto;
				if(j==3 && i== 0)
					p2 = punto;
				if(j==0 && i== 3)
					p4 = punto;
				if(j==3 && i== 3)
					p3 = punto;
			}
			puntoGrosor += grosor/3.0;
		}

		//Guardamos los puntos relevantes en la lista auxiliar
		arrAux.push_back(p1);
		arrAux.push_back(p2);
		arrAux.push_back(p3);
		arrAux.push_back(p4);

		puntoLongitud += length;
	}


	//GENERACIÓN DE CARAS
	list<PV3D> l = list<PV3D>();
	list<PV3D>::iterator itV1 = Panel::_arrVert.begin();
	list<PV3D>::iterator itV2 = Panel::_arrVert.begin();

	
	//Primero generamos las caras que forman las rejillas de los extremos
	for(int i = 0; i < 4; i++)
		itV2++;

	for(int z = 0; z < 2; z++){

		for(int i = 0; i < 3; i++){
		
			for(int j = 0; j < 3; j++){

				p1 = *itV2;
				p2 = *itV1;

				itV1++;
				itV2++;

				p3 = *itV1;
				p4 = *itV2;

				l.push_back(p1);
				l.push_back(p2);
				l.push_back(p3);
				l.push_back(p4);


				// calcula la normal de la cara, con l(vértices de la cara) y lo mete donde está listNorm.
				// Generate normals.
				PV3D norm = Panel::newellNormal(l);

				list<VerticeNormal> listVertNorm = list<VerticeNormal>();

				list<PV3D>::iterator itL = l.begin();
				for(int z = 0; z < l.size();z++){
					listVertNorm.push_back(VerticeNormal(*itL, norm));
					itL++;
					Panel::_arrNorm.push_back(norm);
				}

				Panel::_arrSid.push_back(Cara(listVertNorm.size(), listVertNorm));
				l.clear();
			}

			if(itV2 != Panel::_arrVert.end()){
				itV1++;
				itV2++;
			}
		}

		if(itV2 != Panel::_arrVert.end()){
			for(int i = 0; i < 4; i++){
				itV1++;
				itV2++;
			}
		}
	}

	


	//Ahora generamos las cuatro caras que forman el largo del panel
	itV1 = arrAux.begin();
	itV2 = arrAux.begin();

	for(int i = 0; i < 4; i++)
		itV2++;


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

		if(cont < 3){
			vertAct2 = *itV1;
			vertNext2 = *itV2;
			cont++;
		}else{
			vertAct2 = fstVertAct;
			vertNext2 = fstVertNext;
		}

		l.push_back(vertAct1);
		l.push_back(vertAct2);
		l.push_back(vertNext2);
		l.push_back(vertNext1);

		// calcula la normal de la cara, con l(vértices de la cara) y lo mete donde está listNorm.
		// Generate normals.
		PV3D norm = Panel::newellNormal(l);
		
		list<VerticeNormal> listVertNorm = list<VerticeNormal>();
		
		list<PV3D>::iterator itL = l.begin();
		for(int i = 0; i < l.size();i++){
			listVertNorm.push_back(VerticeNormal(*itL, norm));
			itL++;
			Panel::_arrNorm.push_back(norm);
		}

		Panel::_arrSid.push_back(Cara(listVertNorm.size(), listVertNorm));
		l.clear();
		
	}while(itV2 != arrAux.end());


}

void Panel::draw(){

	list<Cara>::iterator it = Panel::_arrSid.begin();
	while(it != Panel::_arrSid.end()){
		
		glColor3f(0.0, 1.0, 0.0);

		it->draw();
		it++;
	}
}


Panel::~Panel(void)
{
}
