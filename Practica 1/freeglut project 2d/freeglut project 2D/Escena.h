
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


#include "Arbol.h"



using namespace std;



class Escena
{

public:

	Arbol _arbolPitagoras;

	// Scene visible area size
	GLdouble _xLeft, _xRight, _yBot, _yTop;


	void init(const int &WIDTH, const int &HEIGHT);

	void creaArbolPitagoras();

	void draw();

	const int &sizeOfTree();

	void initTree(const Punto &p, const GLdouble &side);

	void colision(const Punto &p);

	void createNextLevel();

	Escena(void);

	~Escena(void);

};

