//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2915
//Purpose: Entry point of the program, setup OpenGl functionality. 
//======================================================================
#include <iostream>
#include <Windows.h>
#include <gl\glut.h>
#include "GlutTime.h"
#include "GameApp.h"

using namespace std;

//================================================================================
void init();
void idle();
void display();
void cleanUp();
void update();
void initalize();
void handleMouse(int x, int y);
void handleKeyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

GlutTime* gp_GlutTime;
GameApp* gp_GameApp;


//================================================================================
int main(int argc, char** argv) {
	
	glutInit(&argc, argv);                 // Initialize GLUT
	initalize();

	return 0;
}

//--------------------------------------------------------------------------------
void initalize()
{
	atexit(cleanUp);

	gp_GlutTime = new GlutTime();
	gp_GlutTime->Init();
	gp_GameApp = new GameApp();
	gp_GameApp->Init();

	

	glutInitWindowSize(720, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Physics");
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	float lightPosition[] = { 0.0, 0.0, -10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	

	glutPassiveMotionFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutReshapeFunc(reshape);

	glutMainLoop();           
}

//--------------------------------------------------------------------------------
void idle()
{
	if (gp_GlutTime->UpdateTime())
	{
		gp_GlutTime->IncrementFrame();
		update();
	}
	
}

//--------------------------------------------------------------------------------
void update()
{
	gp_GameApp->Update();
	glutPostRedisplay(); //Refresh window
}

//--------------------------------------------------------------------------------
void handleMouse(int x, int y)
{
	gp_GameApp->HandleMouse(Vector3D((float)x, (float)y, 0));
}

//--------------------------------------------------------------------------------
void handleKeyboard(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKey(key);
}

//--------------------------------------------------------------------------------
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//glRotatef(1.0f, 0, 0.45f, 0.45f);
	//glTranslated(.01, 0, 0);
	glutSolidCube(0.5);

	glutSwapBuffers();
}

//--------------------------------------------------------------------------------
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);

}

//--------------------------------------------------------------------------------
void cleanUp()
{
	delete gp_GlutTime;
	gp_GlutTime = NULL;

	if (gp_GameApp != NULL)
	{
		gp_GameApp->CleanUp();
	}
	delete gp_GameApp;
	gp_GameApp = NULL;
}
//================================================================================