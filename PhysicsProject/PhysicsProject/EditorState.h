//======================================================================
//File: EditorState.h
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: Saves physics state information such as play and pause
//======================================================================
#ifndef EDITORSTATE_H
#define EDITORSTATE_H
//======================================================================
class EditorState
{
public:
	EditorState();
	~EditorState();

	void Initialize(bool isPaused = false);
	void Play();
	void Pause();
	void ToggleFullScreen();

	inline bool GetIsPaused() const { return m_IsPaused; };
	inline bool GetIsFullScreen() const { return m_IsFullScreen; };
private:
	bool m_IsPaused;
	bool m_IsFullScreen;
};
#endif
//======================================================================