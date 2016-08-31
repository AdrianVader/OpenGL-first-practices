
/* Authors:
			Adrián Rabadán Jurado
			and
			Teresa Rodríguez Ferreira
*/



#include "Malla.h"



void Malla::draw(){
	
	//Colocar el objeto.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glMultMatrixf(*Malla::_tAf._m);

	list<Cara>::iterator it = Malla::_arrSid.begin(); 
    while(it != Malla::_arrSid.end()){ 
          
        glColor3f(0.2, 1.0, 0.3);
  
        it->draw();
        it++;
    }

	glPopMatrix();

}

//Dada una cara devuelve la normal a esa cara
PV3D Malla::newellNormal(list<PV3D> &side){

	PV3D vect = PV3D(0,0,0,0);

	list<PV3D>::iterator it = side.begin();
	PV3D frst = side.front();
	for(int i = 0; i < side.size();i++){
		PV3D act = *it;
		it++;
		PV3D next;
		if(it == side.end())
			next = frst;
		else
			next = *it;
		
		vect._x += (act._y-next._y)*(act._z+next._z);
		vect._y += (act._z-next._z)*(act._x+next._x);
		vect._z += (act._x-next._x)*(act._y+next._y);
	}

	return vect.normalize();
}

Malla::Malla(const GLdouble &largo, const GLdouble &grueso, const GLdouble &x, const GLdouble &y, const GLdouble &z, const GLdouble &rot, const GLdouble &xRot, const GLdouble &yRot, const GLdouble &zRot){

    const GLdouble RAD = 0.0174532925;
	const int LADOS_CUADRADO = 4;
    GLint slices = 2; //Capas que tiene el suelo.
  
    Malla::_numVert = LADOS_CUADRADO * slices; 
  
    Malla::_numNorm = Malla::_numVert; 
  
	Malla::_numSid = Malla::_numVert + 2;
  
    Malla::_arrVert = list<PV3D>();
    Malla::_arrNorm = list<PV3D>();
    Malla::_arrSid = list<Cara>();
      
  
    GLdouble dist = 0; 
    GLdouble alpha = 45, inc = 90;
    for(int i = 0; i < LADOS_CUADRADO; i++){
        Malla::_arrVert.push_back(PV3D((largo/2)*cos(alpha*RAD), (largo/2)*sin(alpha*RAD), dist, 1));
        alpha += inc;
    }
      
    // Create the other side by extrusion.
    int distOld = dist; 
    dist += grueso;
    list<PV3D>::iterator it = Malla::_arrVert.begin(); 
    const int MAX = slices - 1;
    for(int j = MAX-1; j >= 0;j--){ 
        alpha = 0; 
        for(int i = 0; i < LADOS_CUADRADO;i++){ 
            Malla::_arrVert.push_back(PV3D(it->_x, it->_y, it->_z + (dist-distOld), 1));
            it++;
            alpha += inc;
        } 
    }
  
    // Store the faces.
    list<PV3D>::iterator itV1 = Malla::_arrVert.begin(); 
    list<PV3D>::iterator itV2 = Malla::_arrVert.begin(); 
    for(int i = 0; i < LADOS_CUADRADO;i++) 
        itV2++; 
    list<PV3D> l = list<PV3D>(); 
    PV3D fstVertAct = *itV1; 
    PV3D fstVertNext = *itV2; 
    PV3D vertAct1; 
    PV3D vertAct2 = *itV1; 
    PV3D vertNext1; 
    PV3D vertNext2 = *itV2; 
    int cont = 0; 
    do{ 
  
        vertAct1 = *itV1; 
        vertNext1 = *itV2; 
          
        itV1++; 
        itV2++; 
  
        if(cont < LADOS_CUADRADO-1){ 
            vertAct2 = *itV1; 
            vertNext2 = *itV2; 
            cont++; 
        }else{ 
            vertAct2 = fstVertAct; 
            vertNext2 = fstVertNext; 
            cont = 0; 
            if(itV2 !=  Malla::_arrVert.end()){ 
                fstVertAct = *itV1; 
                fstVertNext = *itV2; 
            } 
        } 
  
        l.push_back(vertAct1); 
        l.push_back(vertAct2); 
        l.push_back(vertNext2); 
        l.push_back(vertNext1); 
  
        // calcula la normal de la cara, con l(vértices de la cara) y lo mete donde está listNorm. 
        // Generate normals. 
        PV3D norm = Malla::newellNormal(l); 
          
        list<VerticeNormal> listVertNorm = list<VerticeNormal>(); 
          
        list<PV3D>::iterator itL = l.begin(); 
        for(int i = 0; i < l.size();i++){ 
            listVertNorm.push_back(VerticeNormal(*itL, norm));
            itL++; 
            Malla::_arrNorm.push_back(norm); 
        } 
  
        Malla::_arrSid.push_back(Cara(listVertNorm.size(), listVertNorm)); 
        l.clear(); 
          
    }while(itV2 != Malla::_arrVert.end());

	// Add the top and bottom.
	it = Malla::_arrVert.begin();
	int contador = 0;
	while(it != Malla::_arrVert.end()){

		l.clear();
		contador++;
		for(int i = 0; i < LADOS_CUADRADO;i++){

			if(contador == 0){
				l.push_back(*it);
			}else{
				l.push_front(*it);
			}
			it++;

		}

		PV3D norm = Malla::newellNormal(l); 
          
        list<VerticeNormal> listVertNorm = list<VerticeNormal>(); 
          
        list<PV3D>::iterator itL = l.begin(); 
        for(int i = 0; i < l.size();i++){ 
            listVertNorm.push_back(VerticeNormal(*itL, norm)); 
            itL++;
        } 
  
        Malla::_arrSid.push_back(Cara(listVertNorm.size(), listVertNorm));

	}

	Malla::_tAf.trasladar(PV3D(x, y, z, 0));
	Malla::_tAf.rotar(rot, xRot, yRot, zRot);

}

Malla::~Malla(void){}