
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "TAfin.h"
	


void TAfin::escalar(const PV3D &v){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glScalef(v._x, v._y, v._z);

	GLfloat m[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, *m);

	glPopMatrix();

	TAfin::postmultiplicar(m);
}

void TAfin::trasladar(const PV3D &v){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(v._x, v._y, v._z);

	GLfloat m[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, *m);

	glPopMatrix();

	TAfin::postmultiplicar(m);

}

void TAfin::rotar(const GLdouble &grados, const GLdouble &x, const GLdouble &y, const GLdouble &z){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRotatef(grados, x, y, z);

	GLfloat m[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, *m);

	glPopMatrix();

	TAfin::postmultiplicar(m);

}


void TAfin::postmultiplicar(const GLfloat m[4][4]){

	GLfloat ret[4][4];
	GLfloat r;// Auxiliar.
	for(int i = 0; i < 4;i++){
		for(int j = 0; j < 4;j++){
			r = 0;
			for(int k = 0;k < 4;k++){
				r += TAfin::_m[k][j]*m[i][k];
			}
			ret [i][j] = r;
		}
	}

	for(int i = 0; i < 4;i++){
		for(int j = 0; j < 4;j++){
			TAfin::_m[i][j] = ret[i][j];
		}
	}

}

TAfin::TAfin(void){

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i != j){
				TAfin::_m[i][j] = 0;
			}else{
				TAfin::_m[i][j] = 1;
			}
		}
	}

}

TAfin::~TAfin(void){}