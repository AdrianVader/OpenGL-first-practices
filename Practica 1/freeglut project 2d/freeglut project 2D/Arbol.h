
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include <list>

#include "Cuadrado.h"
#include "Punto.h"



using namespace std;



class Arbol
{

public:

	/*Cuadrado _cuadrado;

	list<Cuadrado> _archivados;
	list<Cuadrado> _frontera;*/

	list<list<Cuadrado>> _arbol;


	void initTree(const Punto &pMid, const GLdouble &side);

	void nextLevel(const Cuadrado &cuadrado);

	void createNextLevel();

	void deleteLastLevel();

	void draw();

	const int &size();

	void colision(const Punto &p);

	Arbol(void);

	~Arbol(void);

};

