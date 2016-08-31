/* Authors: 
            Adrián Rabadán Jurado 
            and 
            Teresa Rodríguez Ferreira 
*/
  
  
#include "Cuadrado.h" 
#include "Punto.h" 
  
  
  
void Cuadrado::createSquare(const Punto &p, const double &side, const double &orientacion, float color[3]){
  
  
	Cuadrado::_orientacion = orientacion;
    Cuadrado::_side = side; 
	Cuadrado::_pointList = list<Punto>();
	Cuadrado::_pointList.push_back(p);
  
    Cuadrado::_initialColor = true; 
	Cuadrado::_color[0] = color[0];
	Cuadrado::_color[1] = color[1];
	Cuadrado::_color[2] = color[2];
	

	Lapiz l = Lapiz(p, orientacion);
	for(int i = 0; i < 3;i++){
		Cuadrado::_pointList.push_back(l.draw(Cuadrado::_side));
		l.turn(90);
	}
  
} 
  
void Cuadrado::draw(){
  
    if(!Cuadrado::_initialColor)
        glColor3f(0.0,0.0,1.0);
	else
		glColor3f(Cuadrado::_color[0], Cuadrado::_color[1], Cuadrado::_color[2]);
		
  
    glBegin ( GL_QUADS ); 
	
	list<Punto>::iterator it = Cuadrado::_pointList.begin();
	Punto p = Punto();
	while(it != Cuadrado::_pointList.end()){
		p = *it;
		glVertex2d(p._x, p._y);
		it++;
	}

    glEnd () ; 
  
    if(!Cuadrado::_initialColor)
		glColor3f(Cuadrado::_color[0], Cuadrado::_color[1], Cuadrado::_color[2]);
  
} 
  
const bool &Cuadrado::colision(const Punto &p, const bool &found){ 
	
	bool encontrado = false;

	if(!found){

		encontrado = true;

		Punto actual;
		Punto siguiente; 
		double asX; // vector anterior->siguiente
		double asY;
		double scX; // vector siguiente->click
		double scY;
		double productoEscalar;

		list<Punto>::iterator it = Cuadrado::_pointList.begin();
		while(it != Cuadrado::_pointList.end()){
		
			actual = *it;
			it++;
			if(it == Cuadrado::_pointList.end()){
				siguiente = *Cuadrado::_pointList.begin();
			}else{
				siguiente = *it;
			}

			asX = siguiente._x - actual._x;
			asY = siguiente._y - actual._y;

			scX = (p._x) - siguiente._x;
			scY = (p._y) - siguiente._y;

			productoEscalar = asX*scX + asY*scY;

			if(productoEscalar > 0)
				encontrado = false;

		}

	}

	if((encontrado && Cuadrado::_initialColor) || (!encontrado && !Cuadrado::_initialColor))
		Cuadrado::changeColor();
  
    return encontrado;
  
} 

const bool &Cuadrado::between(const double &mid, const double &ini, const double &end){

	return ((mid>=ini && mid<=end) || (mid<=ini && mid>=end));

}

void Cuadrado::changeColor(){ 
  
	Cuadrado::_initialColor = !Cuadrado::_initialColor;
  
} 
  
Cuadrado::Cuadrado(void) 
{ 
} 
  
Cuadrado::~Cuadrado(void) 
{ 
} 