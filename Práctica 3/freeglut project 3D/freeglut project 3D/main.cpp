#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>

#include <iostream>

#include "Satelite.h"
#include "CirculoEspiral.h"
#include "Panel.h"



using namespace std;



void drawPlanetWithSatellite();



// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 800, HEIGHT= 600;

// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;

// Camera parameters
GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;



GLUquadricObj* planeta;
Satelite* satelite;
Panel* panel;
CirculoEspiral* espiral;


int contRot;
int contTrans;



void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

    // Light0
    glEnable(GL_LIGHT0);
    GLfloat d[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[]={25.0, 25.0, 0.0, 1.0};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	// buildSceneObjects();

	// Camera set up
	glMatrixMode(GL_MODELVIEW);	//se activa la pila de matrices
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);        
 }


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

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

	
	// Draw the planet and the satellite
	drawPlanetWithSatellite(); // <-- TRY IT with "Q"(forward) and "W"(backward)


	// Draw the spiral.
	espiral->draw();



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
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
}



void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {

		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop ();
			break;

		case 'q':
			contRot++;
			contTrans++;
			break;

		case 'w':
			contRot--;
			if(contTrans > 0)	//Cuando el planeta llega al origen se queda rotando sobre sí mismo
				contTrans--;
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
	cout << "Q para mover el planeta hacia adelante y W para moverlo hacia atrás" << endl;

	int my_window; // my window's identifier



	planeta = gluNewQuadric();
	satelite = new Satelite();
	espiral = new CirculoEspiral();
	panel = new Panel(1);

	contRot = 0;
	contTrans = 0;


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



void drawPlanetWithSatellite(){

	const GLdouble RAD = 0.0174532925;

	glMatrixMode(GL_MODELVIEW);	//Se activa la pila de matrices
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	
	glPushMatrix();	//Se duplica la cima de la pila

	//Realizamos las transformaciones afines para colocar el planeta y el satélite

	//Transformaciones para colocar el planeta
	if(contTrans > 0)
		glTranslatef(0.1*cos(4*contTrans*RAD) + 0.1*contTrans*sin(4*contTrans*RAD), 0, 0.1*sin(4*contTrans*RAD) - 0.1*contTrans*cos(4*contTrans*RAD));
	glRotatef(90, 1, 0, 0);	//Colocamos los polos arriba y abajo
	glRotatef(contRot, 0, 0, 1);	//Rota sobre sí mismo
	
	
	//Draw the sphere.
	glColor3f(0.5,0.0,0.8);
	gluQuadricDrawStyle(planeta, GLU_LINE);//GLU_POINT GLU_LINE GLU_FILL
	//gluSphere(q, radius, slices, stacks);
	gluSphere(planeta, 2, 20, 20);

	
	
	//Deshacemos las transformaciones que hemos usado para pintar el planeta
	glRotatef(-contRot, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);

	//Transformaciones para colocar el satélite
	glRotatef(3*contRot, 0, 1, 0);	//Gira alrededor del planeta
	glTranslatef(0,0,3);	//Lo aleja un poco del planeta
	glRotatef(3*contRot, 0, 0, 1);	//Rota sobre sí mismo


	// Draw the satellite.
	satelite->draw();

	// Draw the four panels
	glTranslatef(0,0,2.4);	//Los colocamos al final del satélite

	glRotatef(90, 1, 0, 0);	//Rotamos cada panel para ponerlo en su posición
	glTranslatef(-0.5,0,0);	//Lo centramos sobre la base del satélite
	panel -> draw();

	glTranslatef(0.5,0,0.5);
	glRotatef(90, 0, 1, 0);
	panel -> draw();

	glTranslatef(0.5,0,0.5);
	glRotatef(90, 0, 1, 0);
	panel -> draw();

	glTranslatef(0.5,0,0.5);
	glRotatef(90, 0, 1, 0);
	panel -> draw();



	glPopMatrix();	//Se elimina la cima duplicada

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

}
