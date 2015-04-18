//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Entry point of the program, setup OpenGl functionality. 
//======================================================================
#include <iostream>
#include <Windows.h>
#include <GL\glew.h>
#include <gl\glut.h>
#include "GlutTime.h"
#include "GameApp.h"
#include "GL/glui.h"
#include "EditorState.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

//================================================================================
void init();
void idle();
void display();
void cleanUp();
void update(float deltaTime);
void initalize();
void handleMouse(int x, int y);
void handleMouseUI(int mouseButton, int mouseState, int x, int y);
void handleKeyPressed(unsigned char key, int x, int y);
void handleKeyReleased(unsigned char key, int x, int y);
void handleGlui(int id);
void reshape(int w, int h);
void updateScreenSize();
//================================================================================
const int ESCAPE_KEY = 27;
const int SPACE_KEY = 32;
const Vector3D INITAL_SCREEN_SIZE = Vector3D(720, 720, 0);
const Vector3D INITAL_WINDOW_POSITION = Vector3D(100, 100, 0);
//================================================================================
GlutTime* gp_GlutTime;
GameApp* gp_GameApp;
EditorState* gp_EditorState;

Vector3D g_ScreenSize = INITAL_SCREEN_SIZE;

bool g_FullScreen = false;
bool g_UseGUIMouse;
int g_MainWindow;

GLUI* g_Glui_subwin;
GLUI_StaticText* g_StaticText;
GLUI_StaticText* g_CollectableText;
GLUI_StaticText* g_WinText;
GLUI_StaticText* g_Time;

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

	srand((unsigned int)time(0));

	gp_GlutTime = new GlutTime();
	gp_GlutTime->Init();
	gp_GameApp = new GameApp();
	
	
	gp_EditorState = new EditorState();

	glutInitWindowSize((int)g_ScreenSize.X, (int)g_ScreenSize.Y);
	glutInitWindowPosition((int)INITAL_WINDOW_POSITION.X, (int)INITAL_WINDOW_POSITION.Y);
	g_MainWindow = glutCreateWindow("Physics");
	
	glewInit();

	float lightPosition[] = { 100.0, 100.0, 100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);
	glutSetCursor(GLUT_CURSOR_NONE);

	gp_GameApp->Init(Vector3D(g_ScreenSize.X, g_ScreenSize.Y, 0.0f));
	updateScreenSize();

	glutIgnoreKeyRepeat(1);
	glutMotionFunc(handleMouse);
	glutPassiveMotionFunc(handleMouse);
	glutKeyboardUpFunc(handleKeyReleased);

	glutDisplayFunc(display);
	GLUI_Master.set_glutKeyboardFunc(handleKeyPressed);
	GLUI_Master.set_glutMouseFunc(handleMouseUI);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutIdleFunc(idle);

	g_Glui_subwin = GLUI_Master.create_glui_subwindow(g_MainWindow, GLUI_SUBWINDOW_BOTTOM);
	g_Glui_subwin->set_main_gfx_window(g_MainWindow);
	g_Glui_subwin->add_button("Play", 3, handleGlui);
	g_Glui_subwin->add_button("Pause", 1, handleGlui);
	g_Glui_subwin->add_button("Stop", 2, handleGlui);
	g_Glui_subwin->add_button("Toggle Debug", 4, handleGlui);
	g_StaticText = g_Glui_subwin->add_statictext("Playing");
	g_UseGUIMouse = false;
	g_Glui_subwin->add_column(1);
	g_CollectableText = g_Glui_subwin->add_statictext("Collectables: ");
	g_WinText = g_Glui_subwin->add_statictext("You haven't won!");

	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));

	gp_EditorState->Pause();
	gp_GameApp->Reset();
	glutPostRedisplay();
	g_StaticText->set_text("Stopped");

	glutMainLoop();           
}

//--------------------------------------------------------------------------------
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
	glutSetWindow(g_MainWindow);
	if (gp_GlutTime->UpdateTime())
	{
		update(gp_GlutTime->GetDeltaTime());
		std::string collectables = "Collectables Left: " + std::to_string(gp_GameApp->GetNumCollectables());
		g_CollectableText->set_text(collectables.c_str());
		g_WinText->set_text((const char*)(gp_GameApp->GetNumCollectables() > 0 ? "You still haven't won!" : "You win!"));
		gp_GlutTime->IncrementFrame();
	}
}

//--------------------------------------------------------------------------------
void update(float deltaTime)
{
	gp_GameApp->Update(deltaTime, gp_EditorState);
	glutPostRedisplay(); //Refresh window

	if (!g_UseGUIMouse)
	{
		SetCursorPos((int)(g_ScreenSize.X / 2.0f) + glutGet(GLUT_WINDOW_X), (int)(g_ScreenSize.Y / 2.0f) + glutGet(GLUT_WINDOW_Y));
	}
}

//--------------------------------------------------------------------------------
void handleMouse(int x, int y)
{
	if (!g_UseGUIMouse)
	{
		gp_GameApp->HandleMouse(Vector3D((float)x, (float)y, 0));
	}
	
}

//--------------------------------------------------------------------------------
void handleMouseUI(int mouseButton, int mouseState, int x, int y)
{

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
		gp_EditorState->ToggleFullScreen();
		if (gp_EditorState->GetIsFullScreen())
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow((int)INITAL_SCREEN_SIZE.X, (int)INITAL_SCREEN_SIZE.Y);
			glutPositionWindow((int)INITAL_WINDOW_POSITION.X, (int)INITAL_WINDOW_POSITION.Y);
		}
		
		updateScreenSize();
	}

	if (key == SPACE_KEY)
	{
		if (g_UseGUIMouse)
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			g_UseGUIMouse = false;
			SetCursorPos((int)(g_ScreenSize.X / 2.0f) + glutGet(GLUT_WINDOW_X), (int)(g_ScreenSize.Y / 2.0f) + glutGet(GLUT_WINDOW_Y));
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_INHERIT);
			g_UseGUIMouse = true;
		}
	}
}

//--------------------------------------------------------------------------------
void handleKeyReleased(unsigned char key, int x, int y)
{
	gp_GameApp->HandleKeyReleased(key);
}

//--------------------------------------------------------------------------------
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	gp_GameApp->Draw();

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
void handleGlui(int id)
{
	switch (id)
	{
	case 1:
		gp_EditorState->Pause();
		g_StaticText->set_text("Paused");
		break;
	case 2:
		gp_EditorState->Pause();
		gp_GameApp->Reset();
		glutPostRedisplay();
		g_StaticText->set_text("Stopped");
		break;
	case 3:
		gp_EditorState->Play();
		g_StaticText->set_text("Playing");
		break;
	case 4:
		GameApp::DebugData = !GameApp::DebugData;
		break;
	case 5:
		GameApp::TimeStep -= 5;
		if (GameApp::TimeStep <= 0)
		{
			GameApp::TimeStep = 1;
		}
		g_Time->set_text(std::string("Simulation Speed: " + std::to_string(GameApp::TimeStep) + " day/second").c_str());
		break;
	case 6:
		GameApp::TimeStep += 5;
		if (GameApp::TimeStep > 100)
		{
			GameApp::TimeStep = 100;
		}
		g_Time->set_text(std::string("Simulation Speed: " + std::to_string(GameApp::TimeStep) + " day/second").c_str());
		break;
	}
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