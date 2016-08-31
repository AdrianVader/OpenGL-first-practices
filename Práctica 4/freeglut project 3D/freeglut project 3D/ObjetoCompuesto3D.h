
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/


#pragma once



#include <list>



#include "Objeto3D.h"



using namespace std;



class ObjetoCompuesto3D : public Objeto3D
{

public:

	list<Objeto3D*> _objList;

	virtual void draw() = 0;

	ObjetoCompuesto3D(void);

	~ObjetoCompuesto3D(void);

};