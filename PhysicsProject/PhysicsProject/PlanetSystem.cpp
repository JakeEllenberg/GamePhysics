//======================================================================
//File: PlanetSystem.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Creats and holds planets but does not own the planet objects
//======================================================================
#include "PlanetSystem.h"

//======================================================================
PlanetSystem::PlanetSystem()
{
}

//--------------------------------------------------------------------------------
PlanetSystem::~PlanetSystem()
{
}

//--------------------------------------------------------------------------------
void PlanetSystem::Initialize()
{
	Planet* sun = new Planet();
	sun->Initialize(.5f, 1988500.0f, Vector3D::Zero, Vector3D::Zero, "Sun");
	Planet* earth = new Planet();
	earth->Initialize(.25f, 5.9725f, Vector3D(1.5f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f,1.0f), "Earth");
	m_Planets.push_back(sun);
	m_Planets.push_back(earth);
}
