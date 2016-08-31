
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
#include <random>
#include <time.h>

#include "escena.h"



using namespace std;



void key(unsigned char key, int x, int y);

void display();

void step(int t);

void initScene();

void mouse(int button,  int state,  int mouseX,  int mouseY);

int initData(int argc, char *argv[]);

void intitGL();


// Viewport size  
int WIDTH = 600, HEIGHT = 450;  

Escena *escena;
bool clicked = false;
bool stepped = true;



int main(int argc, char *argv[]){  

	cout << "Presione * para intercambiar entre movimiento automatico de la pelota o movimiento paso a paso." << endl;
	cout << "Puede mover la pelota paso a paso haciendo click con el raton." << endl;

	int my_window; // my window's identifier

	escena = new Escena();

	escena->init(WIDTH, HEIGHT);

	my_window = initData(argc, argv);


	// We would never reach this point using classic glut  
	system("PAUSE");   

	return 0;  
}


void key(unsigned char key, int x, int y){  

	bool need_redisplay = true;  

	switch (key) {  
	case 27:  /* Escape key */
		//continue_in_main_loop = false; // (**)  
		glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)  
		break;  

	case '*' :
		stepped = !stepped;
		step(1);
		break ;

	default:  
		need_redisplay = false;  
		break;  
	} 

	if (need_redisplay)  
		glutPostRedisplay();  
}

void display(){  
	glClear( GL_COLOR_BUFFER_BIT );  

	if(!clicked){
		initScene();
	}

	escena->draw();
	
	glFlush();
	glutSwapBuffers();

}

void step(int t){
	if(!stepped){
		escena->step();
		glutTimerFunc(10, step, 1);
		glutPostRedisplay();
	}

}

void initScene(){

	srand(time(NULL));

	GLdouble r1 = rand()%100;
	r1 -= 50;
	if(r1 < 0)
		r1 = -1;
	else
		r1 = 1;
		
	GLdouble r2 = rand()%100;
	r2 -= 50;
	if(r2 < 0)
		r2 = -1;
	else
		r2 = 1;
		
	GLdouble rand1 = rand()%100;
	GLdouble rand2 = rand()%100;

	GLdouble modV = sqrt(pow(rand1, 2) + pow(rand2, 2));
		
	escena->createAll(PV2D(200, 225), PV2D(r1*(rand1/modV), r2*(rand2/modV)), 25);
		
	clicked = true;  
	glutPostRedisplay(); 

}

void mouse(int button, int state, int mouseX, int mouseY){ 

	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		escena->step();
		glutPostRedisplay();
	}

}  

int initData(int argc, char *argv[]){  

	//Initialization  
	glutInitWindowSize(WIDTH, HEIGHT);  
	glutInitWindowPosition (140, 140);  
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );  
	glutInit(&argc, argv);  

	//Window construction  
	int my_window = glutCreateWindow( "Pelota" );  

	glutMouseFunc(mouse);  

	//Callback registration
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