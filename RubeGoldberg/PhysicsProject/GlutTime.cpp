//======================================================================
//File: GlutTime.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Keep track of time for a constant frame rate
//======================================================================
#include "GlutTime.h"
#include <iostream>
#include <Windows.h>
#include <gl\glut.h>

//================================================================================
GlutTime::GlutTime()
{

}

//--------------------------------------------------------------------------------
GlutTime::~GlutTime()
{

}

//--------------------------------------------------------------------------------
void GlutTime::Init()
{
	m_StartTime = glutGet(GLUT_ELAPSED_TIME);
	m_LastFrameEnd = m_StartTime;
	m_CurrentFrameNum = 0;
	m_Paused = false;
}

//--------------------------------------------------------------------------------
void GlutTime::Pause()
{
	m_Paused = true;
}

//--------------------------------------------------------------------------------
void GlutTime::Play()
{
	Init();
}

//--------------------------------------------------------------------------------
bool GlutTime::UpdateTime()
{
	if (m_Paused)
	{
		return false;
	}

	int endFrameTime = (int)(m_StartTime + (m_CurrentFrameNum + 1) * TIME_PER_FRAME);
	int endRenderTime = glutGet(GLUT_ELAPSED_TIME);
	int idleTime = endFrameTime - endRenderTime;
	if (idleTime <= 0.0)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
//Returns the time its been since last frame
float GlutTime::GetDeltaTime()
{
	int endRenderTime = glutGet(GLUT_ELAPSED_TIME);

	return (endRenderTime - m_LastFrameEnd) / 1000.0f;
}

//--------------------------------------------------------------------------------
void GlutTime::IncrementFrame()
{
	m_CurrentFrameNum++;
	m_LastFrameEnd = glutGet(GLUT_ELAPSED_TIME);;
}
//================================================================================