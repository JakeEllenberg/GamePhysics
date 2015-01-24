//======================================================================
//File: EditorState.cpp
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: Saves physics state information such as play and pause
//======================================================================
#include "EditorState.h"

//======================================================================
EditorState::EditorState()
{
	m_IsPaused = false;
	m_IsFullScreen = false;
}

//======================================================================
EditorState::~EditorState()
{
}

//--------------------------------------------------------------------------------
void EditorState::Play()
{
	m_IsPaused = false;
}

//--------------------------------------------------------------------------------
void EditorState::Pause()
{
	m_IsPaused = true;
}

//-
void EditorState::ToggleFullScreen()
{
	m_IsFullScreen = !m_IsFullScreen;
}
//======================================================================