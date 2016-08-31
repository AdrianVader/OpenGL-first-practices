#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>

#include <iostream>



#include "Camara.h"
#include "MunecoDeNieve.h"



using namespace std;



void buildSceneObjects();
void drawScenery();
void drawAxis();



// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 800, HEIGHT= 600;

// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;

bool lightOn = true;	//direccional
bool ambientOn = true;	//ambiental
bool posOn = true;	//focos


Camara* camara;
MunecoDeNieve* muneco;

int contX, contY, contZ;



void initGL() {
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

    // Light0 -> Luz direccional con un ángulo de 45º en el plano XZ
    glEnable(GL_LIGHT0);
	GLfloat ambiente0[]={0.3f,0.0f,0.5f,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente0);
	GLfloat pos0[]={1,1,1,0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);

	 // Light1 -> Luz ambiental
    glEnable(GL_LIGHT1);
    GLfloat ambiente1[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente1);

	// Light2 -> Ojo derecho del muñeco
	glEnable(GL_LIGHT2);
	GLfloat difusa2[]={1.0f,1.0f,1.0f,1.0};
	glLightfv(GL_LIGHT2, GL_DIFFUSE, difusa2);
    GLfloat ambiente2[]={1.0f,1.0f,1.0f,1.0};
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 2.0);	// Aplitud
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 4.0);	// Define cómo varía la cantidad de luz

	// Light3 -> Ojo izquierdo del muñeco
	glEnable(GL_LIGHT3);
	GLfloat difusa3[]={1.0f,1.0f,1.0f,1.0};
	glLightfv(GL_LIGHT3, GL_DIFFUSE, difusa3);
    GLfloat ambiente3[]={1.0f,1.0f,1.0f,1.0};
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambiente3);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 2.0);	//Amplitud
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 4.0);	// Define cómo varía la cantidad de luz


	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);



	buildSceneObjects();



	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);        

 }

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  



	drawScenery();



	glFlush();
	glutSwapBuffers();

}

void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(camara->orthoMode){
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	}else{
		gluPerspective(45.0, ((float)WIDTH)/((float)HEIGHT), N, F);
	}
}

void key(unsigned char key, int x, int y){

	bool need_redisplay = true;

	switch (key) {

		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop ();
			break;

		// Recorrido Eje X Y Z.
		case 'r':
			camara->recorridoEje(3,0,0);
			break;
		case 't':
			camara->recorridoEje(-3,0,0);
			break;
		case 'f':
			camara->recorridoEje(0,3,0);
			break;
		case 'g':
			camara->recorridoEje(0,-3,0);
			break;
		case 'v':
			camara->recorridoEje(0,0,3);
			break;
		case 'b':
			camara->recorridoEje(0,0,-3);
			break;
				
		// Giro de las coordenadas mundiales.
		case 'a':
			contX++;
			break;
		case 'z':
			contX--;
			break;
		case 's':
			contY++;
			break;
		case 'x':
			contY--;
			break;
		case 'd':
			contZ++;
			break;
		case 'c':
			contZ--;
			break;

		// Rotación sobre los ejes.
		case '1':
			camara->giraX();
			break;
		case '2':
			camara->giraY();
			break;
		case '3':
			camara->giraZ();
			break;

		// Vista lateral, frontal, cenital y esquina.
		case '4':
			camara->set(15, 0, 0, 0, 1, 0);
			break;
		case '5':
			camara->set(0, 0, 15, 0, 1, 0);
			break;
		case '6':
			camara->set(0, 15, 0, 1, 0, 0);
			break;
		case '7':
			camara->set(45, 45, 45, 0, 1, 0);
			break;
		

		// Roll
		case 'u':
			camara->roll(1);
			break;
		case 'i':
			camara->roll(-1);
			break;

		// Yaw
		case 'j':
			camara->yaw(1);
			break;
		case 'k':
			camara->yaw(-1);
			break;

		// Pitch
		case 'n':
			camara->pitch(1);
			break;
		case 'm':
			camara->pitch(-1);
			break;

		// Cambio de perspectiva.
		case 'p':
			camara->orthoMode = false;
			camara->changePerspective();
			resize(WIDTH, HEIGHT);
			break;
		case 'o':
			camara->orthoMode = true;
			camara->changePerspective();
			resize(WIDTH, HEIGHT);
			break;

		//Luces
		case '8':
			lightOn = !lightOn;
			if(!lightOn)
				glDisable(GL_LIGHT0);// Luz direccional 45º
			else
				glEnable(GL_LIGHT0);
			break;

		case '9':
			ambientOn = !ambientOn;
			if(!ambientOn)
				glDisable(GL_LIGHT1);//Luz ambiental
			else
				glEnable(GL_LIGHT1);
			break;

		// Focos
		case '0':
			posOn = !posOn;
			if(!posOn){
				glDisable(GL_LIGHT2);
				glDisable(GL_LIGHT3);
			}else{
				glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT3);
			}
			break;

		default:
			need_redisplay = false;
			
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}



int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier



	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}



void buildSceneObjects(){

	contX = 0, contY = 0, contZ = 0;

	// Crea el muñeco de nieve.
	muneco = new MunecoDeNieve();

	// Camera parameters.
	camara = new Camara(45.0,45.0,45.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, xLeft, xRight, yTop, yBot, N, F, 45.0, ((float)WIDTH)/((float)HEIGHT));

}

void drawAxis(){

	// Drawing axes
	glBegin( GL_LINES );
		glColor3f(1.0,0.0,0.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(20, 0, 0);	     
	 
		glColor3f(0.0,1.0,0.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);	 
	 
		glColor3f(0.0,0.0,1.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 20);
	glEnd();

}

void drawScenery(){

	glMatrixMode(GL_MODELVIEW);	//Se activa la matriz de modelado-vista
	
	glPushMatrix();	//Se duplica la cima de la pila

	// Giros de la escena, coordenadas mundiales.
	glRotatef(contX*5, 1, 0, 0);
	glRotatef(contY*5, 0, 1, 0);
	glRotatef(contZ*5, 0, 0, 1);


	// Situamos las luces posicionales de los ojos.
	GLfloat dir2[] = {0, 0, 1, 0};
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir2);
	GLfloat pos2[] = {0.25, 4.1, -1.7, 1};
	glLightfv(GL_LIGHT2, GL_POSITION, pos2);

	GLfloat dir3[] = {0, 0, 1, 0};
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir3);
	GLfloat pos3[] = {-0.25, 4.1, -1.7, 1};
	glLightfv(GL_LIGHT3, GL_POSITION, pos3);



	drawAxis();



	muneco->draw();



	glPopMatrix();	//Se elimina la cima duplicada

}
