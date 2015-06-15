#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "Engine.h"
#include "BitmapText.h"
#include "GLLayer.h"
#include "MathStructs.h"

const int MAIN_HEIGHT = 600;
const int MAIN_WIDTH  = 600;
const int SUB_HEIGHT  = 65;
const int SUB_WIDTH   = 275;

const char *VERSION = "2.0";

Engine game;
GLLayer glLayer(&game);
int window[3];

// display function for the left hand side sub window
void display1(void)
{
	/*
	char str[64];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	BitmapText(Point(0.05, 0.33, 0.0), GLUT_BITMAP_8_BY_13).raster(game.infoString(1, str));
	BitmapText(Point(0.05, 0.56, 0.0), GLUT_BITMAP_8_BY_13).raster(game.infoString(2, str));
	BitmapText(Point(0.05, 0.79, 0.0), GLUT_BITMAP_8_BY_13).raster(game.infoString(3, str));

	glutSwapBuffers();
	*/

	glutSetWindow(window[1]);

	glLayer.setViewPoint(GLLayer::LEFT);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glLayer.renderScene();
	glColor3f(1.0, 1.0, 1.0);
	//Pocket::renderSharpPart(Point(0.0, 0.0, 0.0), 180.0, 0.075, 0.1);

	glutSwapBuffers();
}

// display function for the right hand side sub window
void display2(void)
{
	/*
	char str[64];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	BitmapText(Point(0.05, 0.33, 0.0), GLUT_BITMAP_8_BY_13).raster(game.infoString(4, str));
	BitmapText(Point(0.05, 0.56, 0.0), GLUT_BITMAP_8_BY_13).raster(game.infoString(5, str));
	BitmapText(Point(0.05, 0.79, 0.0), GLUT_BITMAP_8_BY_13).raster(game.infoString(6, str));
	glutSwapBuffers();
	*/

	glutSetWindow(window[2]);

	glLayer.setViewPoint(GLLayer::RIGHT);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glLayer.renderScene();
	glColor3f(1.0, 1.0, 1.0);
	//Pocket::renderSharpPart(Point(0.0, 0.0, 0.0), 180.0, 0.075, 0.1);

	glutSwapBuffers();
}

// display function for the main window
void display(void)
{
	glutSetWindow(window[0]);

	glLayer.setViewPoint(GLLayer::RIGHT);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glLayer.renderScene();
	glColor3f(1.0, 1.0, 1.0);
	//Pocket::renderSharpPart(Point(0.0, 0.0, 0.0), 180.0, 0.075, 0.1);

	glutSwapBuffers();
}

// move to the next step, n redisplay the scene
void next(int i)
{
	// move game to the next step
	game.nextStep();
	
	// redisplay windows
	glutSetWindow(window[0]);
	glutPostRedisplay();
	glutSetWindow(window[1]);
	glutPostRedisplay();
	glutSetWindow(window[2]);
	glutPostRedisplay();
	glutTimerFunc(game.timeInterval(), next, 1);
}

// listen to the key board events
void keyboard(unsigned char key, int x, int y)
{
	static GLfloat position[] = {0.0, 0.0, 0.0, 1.0}; 
	switch (key)
	{
	case 'r': case'R':
		game.reset();
		break;
	case 27:
		exit(0);
		break;
	case 'a':
		glLayer.lightsUp();
		break;
	case 'z':
		glLayer.lightsDown();
		break;
	case '1':
		glLayer.turnOff(GLLayer::LAMP1);
		break;
	case '!':
		glLayer.turnOn(GLLayer::LAMP1);
		break;
	case '2':
		glLayer.turnOff(GLLayer::LAMP2);
		break;
	case '@':
		glLayer.turnOn(GLLayer::LAMP2);
		break;

	case 's': case 'S':
		glutSetWindow(window[0]);
		glutReshapeWindow(MAIN_WIDTH, MAIN_HEIGHT);
		break;
	}
}

// lsten to the mouse passive motion
void passiveMotion(int x, int y)
{
	int viewport[4];
	double realX, realY;
	
	// get viewport dimensions
	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y;	// invert y
	// project x and y to our world
	realX = (double) x * (2 / (double) viewport[2]) + (-1.0);
	realY = (double) y * (2 / (double) viewport[3]) + (-1.0);
	
	game.directStick(Point(realX, realY, 0.0));
}

//listen to mouse click events
void mouse(int button, int state, int x, int y)
{
	int viewport[4];
	double realX, realY;
	
	// get viewport dimensions
	glGetIntegerv (GL_VIEWPORT, viewport);
	y = viewport[3] - y;		// invert y
	
	// project x and y on our world
	realX = (double) x * (2 / (double) viewport[2]) + (-1.0);
	realY = (double) y * (2 / (double) viewport[3]) + (-1.0);
	
	if (state == GLUT_UP)
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			game.hit(Point(realX, realY, game.getCue().getRadius()));		
			break;
		case GLUT_RIGHT_BUTTON:
			game.shiftPower();
			break;
		}
}

// reshape function for main window
void reshape(int w, int h)
{
	// calculate sub windows' dimensions
	int sw = w * SUB_WIDTH / MAIN_WIDTH;
	int sh = h * SUB_HEIGHT / MAIN_HEIGHT;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D (0, 1, 0, 1);
	//gluPerspective(60, (GLdouble) w / (GLdouble) h, 0.25, 4);
	glOrtho(-1.0, +1.0, -1.0, +1.0, -2.0, +4.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		0.0, 0.0, 2.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);

	// relocate and reshape sub windows
	glutSetWindow(window[1]);
	glutPositionWindow(0, 0);
	glutReshapeWindow(sw, sh);
	glutSetWindow(window[2]);
	glutPositionWindow(MAIN_WIDTH, 0);
	glutReshapeWindow(sw, sh);
	
	// retrieve focus to the main window
	glutSetWindow(window[0]);
}

// reshape function for sub windows
void reshapeSubWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

}

// initialize the environment for main window
void init(void)

{
	float mat_ambient[] = { 0.0, 0.0, 0.0, 0.0 };

	glClearColor(0.1, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glLayer.initLights();

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	glLayer.turnOn(GLLayer::LAMP1 | GLLayer::LAMP2);
}

// initialize the environment for the sub windows
void initSubWindow(void)
{
	glClearColor (0.3, 0.7, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);
}

// entry point
int main(int argc, char** argv)

{
	printf("GLiardo 2.5 Engraved. Homework Edition.\n");
	printf("Thanks for choosing this game.\n");
	printf("\n");
	printf("Use the mouse to direct the stick.\n");
	printf("Use right mouse botton to adjust the strength.\n");
	printf("Use left mouse botton to hit the ball.\n");
	printf("To restart the game, press 'R'.\n");
	printf("For farther information about the game please read the readme.txt file,\n");
	printf("associated with this game.\n");
	printf("Or contact us at:\n");
	printf("shahwan@scs-net.org\n");
	printf("\n");

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (MAIN_WIDTH * 2, MAIN_HEIGHT);
	glutInitWindowPosition (0, 0);
	window[0] = glutCreateWindow ("Dexter's GLiardo Engraved");
	window[1] = glutCreateSubWindow(window[0], 0, 0, MAIN_WIDTH, MAIN_HEIGHT);
		//glutReshapeFunc(reshape);
		init();
		//initSubWindow();
		glutDisplayFunc(display1);
		glutKeyboardFunc(keyboard);
		glutMouseFunc(mouse);
		glutPassiveMotionFunc(passiveMotion);
	window[2] = glutCreateSubWindow(window[0], MAIN_WIDTH, 0, MAIN_WIDTH, MAIN_HEIGHT);
		//glutReshapeFunc(reshape);
		init();
		//initSubWindow();
		glutDisplayFunc(display2);
		glutKeyboardFunc(keyboard);
		glutMouseFunc(mouse);
		glutPassiveMotionFunc(passiveMotion);
	next(1);
	glutMainLoop();
	return 0;
}
