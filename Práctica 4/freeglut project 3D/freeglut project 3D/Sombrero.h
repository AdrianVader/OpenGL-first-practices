
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


#include "ObjetoCompuesto3D.h"
#include "Disco.h"
#include "Cilindro.h"



using namespace std;



class Sombrero : public ObjetoCompuesto3D
{

public:

	void draw();

	Sombrero(const GLdouble &x, const GLdouble &y, const GLdouble &z);

	~Sombrero(void);

};