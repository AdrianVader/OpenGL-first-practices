
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
#include "Objeto3D.h"



using namespace std;



class Malla : public Objeto3D
{

public:
	//cuyos objetos contienen informaci�n del n�mero de v�rtices, n�mero de 
	//normales y n�mero de caras, junto con los respectivos arrays din�micos de 
	//v�rtices, de normales y de caras.
	
	GLint _numVert; // Number of vertex.
	GLint _numNorm; // Number of normals.
	GLint _numSid; // Number of sides.

	list<PV3D> _arrVert;
	list<PV3D> _arrNorm;
	list<Cara> _arrSid;


	void draw();

	PV3D newellNormal(list<PV3D> &side);

	Malla(const GLdouble &largo, const GLdouble &grueso, const GLdouble &x, const GLdouble &y, const GLdouble &z, const GLdouble &rot, const GLdouble &xRot, const GLdouble &yRot, const GLdouble &zRot);

	~Malla(void);

};