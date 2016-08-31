
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "ObjetoCompuesto3D.h"
	


void ObjetoCompuesto3D::draw(){

	list<Objeto3D*>::iterator it = ObjetoCompuesto3D::_objList.begin();
	while(it != ObjetoCompuesto3D::_objList.end()){

		it._Ptr->_Myval->draw();

		it++;
	}

}

ObjetoCompuesto3D::ObjetoCompuesto3D(void){}

ObjetoCompuesto3D::~ObjetoCompuesto3D(void){}