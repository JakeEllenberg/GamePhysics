//======================================================================
//File: FireWorkLauncher.cpp
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: Containts fireworks and managers making more on explosion
//======================================================================
#define _USE_MATH_DEFINES
#include "FireworkLauncher.h"
#include <math.h>

//======================================================================
FireworkLauncher::FireworkLauncher()
{
	m_MinExpFireworks = 0;
	m_MaxExpFireworks = 0;
	m_MinLifeTime = 0;
	m_MaxLifeTime = 0;
	m_ExpChance = 0;
	m_MinSpeed = 0;
	m_MaxSpeed = 0;
}

//======================================================================
FireworkLauncher::~FireworkLauncher()
{
}

//--------------------------------------------------------------------------------
void FireworkLauncher::Initialzie(Vector3D startPos, Vector3D startVelocity, int startLifeTime, int minExpFireworks, 
	int maxExpFireworks, int minLifeTime, int maxLifeTime, int expChance, float minSpeed, float maxSpeed, int maxFireWorks, int numLevels)
{
	m_MinExpFireworks = minExpFireworks;
	m_MaxExpFireworks = maxExpFireworks;
	m_MinLifeTime = minLifeTime;
	m_MaxLifeTime = maxLifeTime;
	m_ExpChance = expChance;
	m_MinSpeed = minSpeed;
	m_MaxSpeed = maxSpeed;
	m_MaxFireworks = maxFireWorks;
	m_StartPosition = startPos;
	m_StartVelocity = startVelocity;
	m_StartLifeTime = startLifeTime;
	m_NumLevels = numLevels;
	m_CurrentLevel = 0;

	Firework* startFireWork = new Firework();
	startFireWork->Inititalize(true, (float)startLifeTime, startPos, startVelocity);
	m_Fireworks.push_back(startFireWork);
}

//--------------------------------------------------------------------------------
void FireworkLauncher::Update(float deltaTime)
{
	std::vector<Firework*>::iterator iter;
	std::vector<Firework*> fireworksToExplode;
	for (iter = m_Fireworks.begin(); iter != m_Fireworks.end(); iter++)
	{
		(*iter)->Update(deltaTime);
		if (!(*iter)->CheckAlive())
		{
			fireworksToExplode.push_back(*iter);
		}
	}

	std::vector<Firework*>::iterator iter2;

	if (fireworksToExplode.size() > 0)
	{
		m_CurrentLevel++;
	}
	for (iter2 = fireworksToExplode.begin(); iter2 != fireworksToExplode.end(); iter2++)
	{
		Firework* firework = (*iter2);
		GenerateExplosion(firework->GetPosition());
	}

	for (unsigned int index = 0; index < m_Fireworks.size(); index++)
	{
		if (!m_Fireworks[index]->CheckAlive())
		{
			delete m_Fireworks[index];
			m_Fireworks.erase(m_Fireworks.begin() + index);
			index--;
		}
	}
}

//--------------------------------------------------------------------------------
void FireworkLauncher::Draw()
{
	std::vector<Firework*>::iterator iter;
	for (iter = m_Fireworks.begin(); iter != m_Fireworks.end(); iter++)
	{
		(*iter)->Draw();
	}
}

//--------------------------------------------------------------------------------
int FireworkLauncher::getNumExp()
{
	return m_MinExpFireworks + (rand() % (m_MaxExpFireworks - m_MinExpFireworks));
}

//--------------------------------------------------------------------------------
int FireworkLauncher::getLifeTime()
{
	return m_MinLifeTime + (rand() % (m_MaxLifeTime - m_MinLifeTime));
}

//--------------------------------------------------------------------------------
bool FireworkLauncher::getIsExploading()
{
	return rand() % m_ExpChance == 1;
}

//--------------------------------------------------------------------------------
float FireworkLauncher::getSpeed()
{
	return m_MinSpeed + (rand() / (RAND_MAX / (m_MaxSpeed - m_MinSpeed)));
}

//--------------------------------------------------------------------------------
//Used http://math.stackexchange.com/questions/44689/how-to-find-a-random-axis-or-unit-vector-in-3d
//as a reference
Vector3D FireworkLauncher::getVelocity(float speed)
{
	Vector3D velocity;
	float randomRotation = (float)(rand() / (float)(RAND_MAX / (M_PI))); //random value 0-PI
	float randomZ = -1.0f + (float)(rand() / (float)(RAND_MAX / (2))); //random value from -1-1
	velocity.X = sqrt(1 - pow(randomZ, 2)) * cos(randomRotation);
	velocity.Y = sqrt(1 - pow(randomZ, 2)) * sin(randomRotation);
	velocity.Z = randomZ;
	return velocity.Normalized() * speed;
}

//--------------------------------------------------------------------------------
void FireworkLauncher::GenerateExplosion(Vector3D startingPosition)
{
	if ((int)m_Fireworks.size() >= m_MaxFireworks || m_CurrentLevel >= m_NumLevels)
	{
		return;
	}

	int numFireworks = getNumExp();
	int lifeTime = getLifeTime();
	float speed = getSpeed();

	for (int i = 0; i < numFireworks; i++)
	{
		
		Firework* newFirework = new Firework();
		newFirework->Inititalize(getIsExploading(), (float)lifeTime, startingPosition, getVelocity(speed));
		m_Fireworks.push_back(newFirework);
	}
}

//--------------------------------------------------------------------------------
void FireworkLauncher::CleanUp()
{
	std::vector<Firework*>::iterator iter;
	for (iter = m_Fireworks.begin(); iter != m_Fireworks.end(); iter++)
	{
		delete *iter;
	}
	m_Fireworks.clear();
}

//--------------------------------------------------------------------------------
void FireworkLauncher::Reset()
{
	CleanUp();

	Firework* startFireWork = new Firework();
	startFireWork->Inititalize(true, (float)m_StartLifeTime, m_StartPosition, m_StartVelocity);
	m_Fireworks.push_back(startFireWork);
	m_CurrentLevel = 0;
}