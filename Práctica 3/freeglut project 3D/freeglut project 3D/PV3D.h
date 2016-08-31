
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



using namespace std;



class PV3D
{

public:

	GLdouble _x; // Point or vector in x's axis. 
    GLdouble _y; // Point or vector in y's axis.
	GLdouble _z; // Point or vector in z's axis.
	GLint _point; // = 1 if it is a point, = 0 if it's a vector.
  

	PV3D normalize();

    PV3D(const GLdouble &x, const GLdouble &y, const GLdouble &z, const GLint &point);

	PV3D(void);

	~PV3D(void);

};