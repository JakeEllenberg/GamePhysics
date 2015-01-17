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

	glutInitWindowSize(1280, 720);   // Set the window's initial width & height
	glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
	glutCreateWindow("Physics"); // Create a window with the given title
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutIdleFunc(idle);
	glutMainLoop();           // Enter the infinitely event-processing loop
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
	glutPostRedisplay(); //Refresh window
}

//--------------------------------------------------------------------------------
void display() {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	glRotatef(1, 0, 50, 0);
	glutWireCube(1.0);

	glFlush();  // Render now
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