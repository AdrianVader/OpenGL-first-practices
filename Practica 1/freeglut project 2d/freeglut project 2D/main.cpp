
/* Authors:  
Adrián Rabadán Jurado  
and  
Teresa Rodríguez Ferreira  
*/


#include <Windows.h>  
#include <gl/GL.h>  
#include <gl/GLU.h>  
#include <GL/freeglut.h> 

#include <iostream>  


#include "escena.h"



using namespace std;



void resize(int newWidth, int newHeight);

void key(unsigned char key, int x, int y);

void mueveEnX(const bool &izq);

void mueveEnY(const bool &arr);

void zoom(const bool &in);

void display();

void mouse(int button,  int state,  int mouseX,  int mouseY);

void embaldosar(const int &numCol);

int initData(int argc, char *argv[]);

void intitGL();


// Viewport size  
int WIDTH = 500, HEIGHT = 250;  

Escena *escena;
bool clicked = false;  
GLdouble side;
bool embaldosado = false;
int numCol;



int main(int argc, char *argv[]){  



	cout << "Starting console..." << endl;
	cout << "Introduzca el lado del cuadrado: " << endl;
	cin >> side;

	//Muestra el menú con las diferentes opciones
	cout << endl << "a: desplazar area visible a la izquierda" << endl;
	cout << "d: desplazar area visible a la derecha" << endl;
	cout << "w: desplazar area visible hacia arriba" << endl;
	cout << "s: desplazar area visible hacia abajo" << endl;
	cout << "q: aumentar zoom progresivo" << endl;
	cout << "e: disminuir zoom progresivo" << endl;
	cout << "+: aniadir un nivel" << endl;
	cout << "-: quitar un nivel" << endl;
	cout << "*: embaldosar" << endl;


	int my_window; // my window's identifier  

	escena = new Escena(); 

	escena->init(WIDTH, HEIGHT);

	my_window = initData(argc, argv);  


	// We would never reach this point using classic glut  
	system("PAUSE");   

	return 0;  
}


void resize(int newWidth, int newHeight){  

	//Resize Viewport  
	WIDTH= newWidth;  
	HEIGHT= newHeight;  
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;  
	glViewport ( 0, 0, WIDTH, HEIGHT );  

	//Resize Scene Visible Area   
	//Se actualiza el área visible de la escena  
	//para que su ratio coincida con ratioViewPort  
	GLdouble SVAWidth= escena->_xRight - escena->_xLeft;  
	GLdouble SVAHeight= escena->_yTop - escena->_yBot;  
	GLdouble SVARatio= SVAWidth/SVAHeight;  
	if (SVARatio >= RatioViewPort) {  
		// Increase SVAHeight  
		GLdouble newHeight= SVAWidth/RatioViewPort;  
		GLdouble yMiddle= ( escena->_yBot + escena->_yTop )/2.0;  
		escena->_yTop= yMiddle + newHeight/2.0;  
		escena->_yBot= yMiddle - newHeight/2.0;  
	}  
	else {  
		//Increase SVAWidth  
		GLdouble newWidth= SVAHeight*RatioViewPort;  
		GLdouble xMiddle= ( escena->_xLeft + escena->_xRight )/2.0;  
		escena->_xRight= xMiddle + newWidth/2.0;  
		escena->_xLeft=  xMiddle - newWidth/2.0;  
	}  

	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	gluOrtho2D(escena->_xLeft, escena->_xRight, escena->_yBot, escena->_yTop);  
}

void key(unsigned char key, int x, int y){  

	bool need_redisplay = true;

	switch (key) {  
	case 27:  /* Escape key */
		//continue_in_main_loop = false; // (**)  
		glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)  
		break;  

	case 'a' :
		mueveEnX(true);
		break ;  

	case 'd' :
		mueveEnX(false);
		break ;  

	case 'w' :
		mueveEnY(true);
		break ;  

	case 's' :
		mueveEnY(false);
		break ;  

	case 'q' :
		zoom(true);
		break ;  

	case 'e' :
		zoom(false);
		break ;  

	case '+' :
		if(clicked)
			escena->createNextLevel();
		break ;

	case '-' :
		if(clicked && escena->sizeOfTree() > 1)
			escena->_arbolPitagoras.deleteLastLevel();
		break ;

	case '*' :
		cout << "Introduce el numero de columnas(0 o negativo para cancelar): ";
			cin >> numCol;
		if(numCol <= 0){
			embaldosado = false;
			glViewport(0, 0, WIDTH, HEIGHT);
		}else{
			embaldosado = true;
		}
		break ;

	default:  
		need_redisplay = false;  
		break;  
	} 

	if (need_redisplay)  
		glutPostRedisplay();  
}

//Mueve el área visible hacia la izquierda (true) o derecha (false)
void mueveEnX(const bool &izq){

	int signo;
	if(izq){
		signo = 1;
	}else{
		signo = -1;
	}

	GLdouble ancho = (escena->_xRight - escena->_xLeft);

	escena->_xLeft -= signo*ancho*0.02;
	escena->_xRight -= signo*ancho*0.02;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(escena->_xLeft, escena->_xRight, escena->_yBot, escena->_yTop);

}

//Mueve el área visible hacia arriba (true) o abajo (false)
void mueveEnY(const bool &arr){

	int signo;
	if(arr){
		signo = 1;
	}else{
		signo = -1;
	}

	GLdouble alto = (escena->_yTop - escena->_yBot);

	escena->_yTop += signo*alto*0.02;
	escena->_yBot += signo*alto*0.02;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(escena->_xLeft, escena->_xRight, escena->_yBot, escena->_yTop);
}

//Aumenta (true) o disminuye (false) el zoom
void zoom(const bool &in){ 

	int sign; 
	if(in) 
		sign = 1; 
	else
		sign = -1; 

	GLdouble ancho = (escena->_xRight - escena->_xLeft), alto = (escena->_yTop - escena->_yBot); 
	int nIter = 5; 
	GLdouble fIncr = (sign*0.1)/(GLdouble)nIter; 

	for(int i = 1; i <= nIter; i++){
		escena->_xLeft += ancho*fIncr;
		escena->_xRight -= ancho*fIncr;
		escena->_yTop -= alto*fIncr;
		escena->_yBot += alto*fIncr;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(escena->_xLeft, escena->_xRight, escena->_yBot, escena->_yTop);

		display();
		Sleep(25);
	} 

}

void display(){  
	glClear( GL_COLOR_BUFFER_BIT );  

	if(embaldosado){

		embaldosar(numCol);

	}else{

		if(clicked)  
			escena->draw();

	}

	glFlush();  
	glutSwapBuffers(); 
}

void mouse(int button, int state, int mouseX, int mouseY){ 

	int error = -4;

	Punto pMid;

	if(embaldosado){
		pMid = Punto(mouseX, (HEIGHT-mouseY + error));

		GLdouble SVAratio = (escena->_xRight-escena->_xLeft)/(escena->_yTop-escena->_yBot);
		GLdouble wid = WIDTH/numCol;
		GLdouble hei = wid/SVAratio;

		int vueltasX = pMid._x/wid;
		int vueltasY = pMid._y/hei;

		pMid._x = pMid._x - vueltasX*wid;

		pMid._y = pMid._y - vueltasY*hei;

		pMid._x *= numCol;
		pMid._y *= HEIGHT/hei;

		pMid._x *= ((escena->_xRight-escena->_xLeft)/WIDTH);
		pMid._y *= ((escena->_yTop-escena->_yBot)/HEIGHT);

		pMid._x += escena->_xLeft;
		pMid._y += escena->_yBot;

	}else{

		pMid = Punto(escena->_xLeft+((escena->_xRight-escena->_xLeft)/WIDTH)*mouseX, escena->_yBot+((escena->_yTop-escena->_yBot)/HEIGHT)*(HEIGHT-mouseY + error));

	}

	if(!clicked){

		if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){  

			escena->initTree(pMid, side);

			clicked = true;  
			glutPostRedisplay();  
		}  

	}else{

		escena->colision(pMid);

	}  

}  

void embaldosar(const int &numCol){

	GLdouble SVAratio = (escena->_xRight-escena->_xLeft)/(escena->_yTop-escena->_yBot);
	GLdouble wid = WIDTH/numCol;

	GLdouble hei = wid/SVAratio;

	for(GLint c = 0; c < numCol; c++){
		GLdouble currentH = 0;
		while((currentH + hei) < HEIGHT){
			glViewport((c*wid), currentH, wid, hei);
			escena->draw();
			currentH += hei;
		}
	}

}

int initData(int argc, char *argv[]){  

	//Initialization  
	glutInitWindowSize(WIDTH, HEIGHT);  
	glutInitWindowPosition (140, 140);  
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );  
	glutInit(&argc, argv);  

	//Window construction  
	int my_window = glutCreateWindow( "Arbol de Pitagoras" );  

	glutMouseFunc(mouse);  

	//Callback registration  
	glutReshapeFunc(resize);  
	glutKeyboardFunc(key);  
	glutDisplayFunc(display);  


	//OpenGL basic setting  
	intitGL();  


	// Freeglut's main loop can be stopped executing (**)  
	//while ( continue_in_main_loop )  
	//  glutMainLoopEvent();  

	// Classic glut's main loop can be stopped after X-closing the window,  
	// using the following freeglut's setting (*)  
	glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;  

	// Classic glut's main loop can be stopped in freeglut using (*)  
	glutMainLoop();   

	return my_window;  

}

void intitGL(){  

	glClearColor(1.0,1.0,1.0,1.0);  
	glColor3f(0.70,0.30,0.00);   

	glPointSize(4.0);
	glLineWidth(2.0);

	// Viewport  
	glViewport(escena->_xLeft, escena->_yBot, WIDTH, HEIGHT);  

	// Model transformation  
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();  

	// Scene Visible Area  
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	gluOrtho2D(escena->_xLeft, escena->_xRight, escena->_yBot, escena->_yTop);   
}