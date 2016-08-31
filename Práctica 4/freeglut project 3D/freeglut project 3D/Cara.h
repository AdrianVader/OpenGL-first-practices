
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

#include <list>

#include "PV3D.h"
#include "VerticeNormal.h"



using namespace std;



class Cara
{

public:

	GLint _numVert; // N�mero de v�rtices que forman la cara

	list<VerticeNormal> _norm; // Normals


	void draw();

	Cara(GLint numVert, list<VerticeNormal> norm);

	Cara(void);

	~Cara(void);

};