
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


#include "ObjetoCuadrico.h"



using namespace std;



class Cilindro : public ObjetoCuadrico
{

public:

	GLdouble _radioSuperior;	//Para la nariz

	GLdouble _altura;

	void draw();

	Cilindro::Cilindro(const GLdouble &radioInf, const GLdouble &radioSup, const GLdouble &altura, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &x, const GLdouble &y, const GLdouble &z);

	Cilindro::Cilindro(const GLdouble &radioInf, const GLdouble &radioSup, const GLdouble &altura, const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &x, const GLdouble &y, const GLdouble &z, const GLdouble &rot, const GLdouble &xRot, const GLdouble &yRot, const GLdouble &zRot);

	~Cilindro(void);

};