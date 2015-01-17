//======================================================================
//File: GlutTime.cpp
//Author: Jake Ellenberg
//Created: 1/17/2915
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
	m_CurrentFrameNum = 0;
}

//--------------------------------------------------------------------------------
bool GlutTime::UpdateTime()
{
	double endFrameTime = m_StartTime + (m_CurrentFrameNum + 1) * TIME_PER_FRAME;
	double endRenderTime = glutGet(GLUT_ELAPSED_TIME);
	double idleTime = endFrameTime - endRenderTime;
	if (idleTime <= 0.0)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
void GlutTime::IncrementFrame()
{
	m_CurrentFrameNum++;
}
//================================================================================