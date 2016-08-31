
/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
*/


#pragma once



#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>



#include "PV3D.h"
#include "Cara.h"



using namespace std;



class Malla
{

public:
	//cuyos objetos contienen informaci�n del n�mero de v�rtices, n�mero de 
	//normales y n�mero de caras, junto con los respectivos arrays din�micos de 
	//v�rtices, de normales y de caras.
	
	GLint _numVert; // Number of vertex.
	GLint _numNorm; // Number of normals.
	GLint _numSid; // Number of sides.

	list<PV3D> _arrVert;// ASDF ** � [] <-no me fnciona =S // Dynamic array of vertex.
	list<PV3D> _arrNorm;// ASDF ** � [] <-no me fnciona =S // Dynamic array of normals.
	list<Cara> _arrSid;// ASDF ** � [] <-no me fnciona =S // Dynamic array of sides.

	PV3D newellNormal(list<PV3D> &side);

	Malla(void);

	~Malla(void);

};