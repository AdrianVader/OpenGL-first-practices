/* Authors:
			Adri�n Rabad�n Jurado
			and
			Teresa Rodr�guez Ferreira
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

