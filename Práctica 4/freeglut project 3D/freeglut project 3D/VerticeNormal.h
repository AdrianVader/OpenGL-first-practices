
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#include "PV3D.h"



using namespace std;



class VerticeNormal
{

public:

	PV3D _vert; // index of vertex.
	PV3D _norm; // index of vertex's normal.


	VerticeNormal(const PV3D &vert, const PV3D &norm);

	VerticeNormal(void);

	~VerticeNormal(void);

};