/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "Malla.h"



#pragma once



class Panel : public Malla
{
public:

	void draw();

	Panel(GLdouble width);

	~Panel(void);
};

