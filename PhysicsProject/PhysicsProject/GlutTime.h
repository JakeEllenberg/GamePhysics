//======================================================================
//File: GlutTime.h
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Keep track of time for a constant frame rate
//======================================================================
#ifndef GLUTTIME_H
#define GLUTTIME_H
const unsigned int TARGET_FPS = 60;
const double TIME_PER_FRAME = 1000.0 / TARGET_FPS;


//================================================================================
class GlutTime
{
public:
	GlutTime();
	~GlutTime();
	void Init();
	bool UpdateTime();
	void IncrementFrame();
	void Pause();
	void Play();
private:
	double m_StartTime;
	int m_CurrentFrameNum;
	bool m_Paused;
};
#endif
//================================================================================