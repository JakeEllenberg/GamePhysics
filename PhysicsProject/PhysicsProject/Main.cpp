//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
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
void handleKeyPressed(unsigned char key, int x, int y);
void handleKeyReleased(unsigned char key, int x, int y);
void reshape(int w, int h);
void updateScreenSize();
//================================================================================
const int ESCAPE_KEY = 27;
const Vector3D INITAL_SCREEN_SIZE = Vector3D(720, 720, 0);
const Vector3D INITAL_WINDOW_POSITION = Vector3D(100, 100, 0);
//================================================================================
GlutTime* gp_GlutTime;
GameApp* gp_GameApp;

Vector3D g_ScreenSize = INITAL_SCREEN_SIZE;

int angle;
bool g_FullScreen = false;

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
	gp_GameApp->Init(Vector3D(g_ScreenSize.X, g_ScreenSize.Y, 0.0f));
	angle = 0;

	glutInitWindowSize((int)g_ScreenSize.X, (int)g_ScreenSize.Y);
	glutInitWindowPosition((int)INITAL_WINDOW_POSITION.X, (int)INITAL_WINDOW_POSITION.Y);
	glutCreateWindow("Physics");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	updateScreenSize();

	float lightPosition[] = { 100.0, 100.0, 100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glutSetCursor(GLUT_CURSOR_NONE);

	glutIgnoreKeyRepeat(1);
	glutMotionFunc(handleMouse);
	glutPassiveMotionFunc(handleMouse);
	glutKeyboardFunc(handleKeyPressed);
	glutKeyboardUpFunc(handleKeyReleased);
	glutReshapeFunc(reshape);
	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));

	glutMainLoop();           
}

//--------------------------------------------------------------------------------
//Using windows functions to calculte the window size
//and glut functions to calculate the screen size for our camera class
void updateScreenSize()
{
	RECT windowRect;
	HWND mainWindowHandle = FindWindow(NULL, "Physics");
	GetWindowRect(mainWindowHandle, &windowRect);

	g_ScreenSize.X = (float)glutGet(GLUT_WINDOW_WIDTH);
	g_ScreenSize.Y = (float)glutGet(GLUT_WINDOW_HEIGHT);
	gp_GameApp->UpdateScreenSize(Vector3D(g_ScreenSize.X, g_ScreenSize.Y, 0));
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
	angle = (angle + 1) % 360;
	gp_GameApp->Update();
	glutPostRedisplay(); //Refresh window
	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));
}

//--------------------------------------------------------------------------------
void handleMouse(int x, int y)
{
	gp_GameApp->HandleMouse(Vector3D((float)x + glutGet(GLUT_WINDOW_X), (float)y + glutGet(GLUT_WINDOW_Y), 0));
}

//--------------------------------------------------------------------------------
void handleKeyPressed(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyPressed(key);

	if (key == ESCAPE_KEY)
	{
		exit(0);
	}

	if (key == 'f')
	{
		if (g_FullScreen)
		{
			glutReshapeWindow((int)INITAL_SCREEN_SIZE.X, (int)INITAL_SCREEN_SIZE.Y);
			glutPositionWindow((int)INITAL_WINDOW_POSITION.X, (int)INITAL_WINDOW_POSITION.Y);
			g_FullScreen = false;
		}
		else
		{
			glutFullScreen();
			g_FullScreen = true;
		}
		
		updateScreenSize();
	}
	
	if (key == 'b')
	{
		int x = 5;
	}
}

void handleKeyReleased(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyReleased(key);
}

//--------------------------------------------------------------------------------
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glPushMatrix();
	glRotatef((float)angle, 0, 0.45f, 0.45f);
	glutSolidCube(0.5);
	glPopMatrix();

	glutSwapBuffers();
}

//--------------------------------------------------------------------------------
void reshape(int w, int h) {
	updateScreenSize();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
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